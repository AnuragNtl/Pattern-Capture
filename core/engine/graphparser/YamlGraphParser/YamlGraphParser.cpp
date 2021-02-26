#include<set>
#include "YamlGraphParser.h"

using namespace PatternCapture;

Graph* YamlGraphParser :: parse(const char *graphSpec) {
    istringstream in(graphSpec);
    cout << graphSpec << "\n";
    YAML::Node doc = YAML::Load(graphSpec);
    if(!doc.IsMap()) {
        throw std::exception();
    }
    Graph *graph = new Graph;
    addGraphProperties(*graph, doc);
    addAllHooksProperties(*graph, doc);
    addNodeFrom(doc, NULL, *graph);
    return graph;
}

void YamlGraphParser :: addGraphProperties(Graph &graph, const YAML::Node &node) {
    const YAML::Node graphProperties = node[GRAPH_PROPERTIES];
    if(graphProperties.IsDefined() && graphProperties.IsMap()) {
        for(const auto &property : graphProperties) {
            graph.properties[property.first.as<string>()] = property.second.as<string>();
        }
    }

}

void YamlGraphParser :: addAllHooksProperties(Graph &graph, const YAML::Node &node) {
    const auto &hookProperties = node[HOOKS_PROPERTIES];
    if(!(hookProperties.IsDefined() && hookProperties.IsMap())) return;
    for(const auto &hookSpecItem : hookProperties) {
        addHookProperties(graph, hookSpecItem, hookSpecItem.first.as<string>());
    }
}

void YamlGraphParser :: addHookProperties(Graph &graph, const YAML::Node &hookSpec, const string hookName) {
    for(const auto &hookSpecItem : hookSpec) {
        graph[hookName][hookSpecItem.first.as<string>()] = hookSpecItem.second.as<string>();
    }
}

Node* YamlGraphParser :: addNodeFrom(const YAML::Node &node, Node *comesFrom, Graph &graph) {
    bool isRoot = false;
    string nodeId = node[NODE_ID].as<string>(),
           type = node[NODE_TYPE] ? node[NODE_TYPE].as<string>() : string(),
           dependencyId = node[NODE_DEPENDENCY_ID].as<string>();
           YAML::Node deliversToNodes = node[NODE_DELIVERS_TO],
           acceptsFromNodesSpec = node[NODE_ACCEPTS_FROM];
    set<string> acceptsFromNodes;

    if(comesFrom != NULL) {
        acceptsFromNodes.insert(comesFrom->id);
    } else {
        isRoot = true;
    }
    map<string, string> inputParams;

    for(const YAML::Node &acceptsFromNode : acceptsFromNodesSpec) {
        acceptsFromNodes.insert(acceptsFromNode.as<string>());
    }

    if(node[NODE_INPUT_PARAMS]) {
        for(const auto &value : node[NODE_INPUT_PARAMS]) {
            inputParams[value.first.as<string>()] = value.second.as<string>();
        }
    }
    Node *graphNode = graph.addNode(nodeId, type, dependencyId, acceptsFromNodes, inputParams);
    graphNode->isRoot = isRoot;
    for(const auto &deliversToNode : deliversToNodes) {
        Node *deliversToGraphNode = addNodeFrom(deliversToNode, graphNode, graph);
        graphNode->addDeliversToNode(deliversToGraphNode);
    }
    return graphNode;

}



