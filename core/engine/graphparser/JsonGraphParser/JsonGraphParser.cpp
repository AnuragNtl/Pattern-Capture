#include <iostream>
#include "JsonGraphParser.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <vector>
#include <set>
#include <map>
#include <boost/exception/diagnostic_information.hpp>

using namespace std;
using namespace PatternCapture;
using namespace boost::property_tree;

ptree empty_ptree;


Graph* JsonGraphParser :: parse(const char *input) {
   
    ptree graphSpec;
    string inputData = input;
    
    istringstream graphSpecInput(inputData);
    
    try {
        Graph *graph = new Graph;
        read_json(graphSpecInput, graphSpec);
        addGraphProperties(*graph, graphSpec);
        addHooksProperties(*graph, graphSpec);
        addNodeFrom(graphSpec, NULL, *graph); return graph; } catch(boost::exception &e) { throw GraphParseException("Cannot parse graph from JSON specified" + boost::diagnostic_information(e)); } }


Node* JsonGraphParser :: addNodeFrom(ptree node, Node *comesFrom, Graph &graph) {
    string nodeId = node.get_child(NODE_ID).get_value<string>();
    boost :: optional<ptree &> typeOpt = node.get_child_optional(NODE_TYPE);
    string type;
    if(typeOpt) {
        type = typeOpt->get_value<string>();
    }
    string dependencyId = node.get_child(NODE_DEPENDENCY_ID).get_value<string>();
    ptree &deliversToNodes = node.get_child_optional(NODE_DELIVERS_TO).value_or(empty_ptree);
    ptree acceptsFromNodesSpec = node.get_child_optional(NODE_ACCEPTS_FROM).value_or(empty_ptree);
    set<string> acceptsFromNodes;
    bool isRoot = false;
    if(comesFrom != NULL) {
        acceptsFromNodes.insert(comesFrom->id);
    } else {
        isRoot = true;
    }

    map<string, string> inputParams;

    for(auto &acceptsFromNode : acceptsFromNodesSpec) {
        acceptsFromNodes.insert(acceptsFromNode.second.get_value<string>());
    }

    for(auto inputParamSpec : node.get_child_optional(NODE_INPUT_PARAMS).value_or(empty_ptree)) {

        inputParams[inputParamSpec.first] = inputParamSpec.second.get_value<string>();
    }

    Node *graphNode = graph.addNode(nodeId, type, dependencyId, acceptsFromNodes, inputParams);
    graphNode->isRoot = isRoot;
    for(auto &deliversToNode : deliversToNodes) {
        Node *deliversToGraphNode = addNodeFrom(deliversToNode.second, graphNode, graph);
        graphNode->addDeliversToNode(deliversToGraphNode);
    }
    return graphNode;
}

void JsonGraphParser :: addGraphProperties(Graph &graph, const ptree &root) {
    ptree graphPropertiesSpec = root.get_child_optional(GRAPH_PROPERTIES).value_or(empty_ptree);
    for(auto propertySpec : graphPropertiesSpec) {
        graph.addProperty(propertySpec.first, propertySpec.second.get_value<string>());
    }
    
}

void JsonGraphParser :: addHookProperties(Graph &graph, const ptree &hookSpec, string hookName) {

    for(auto hookSpecItem : hookSpec) {
        graph[hookName][hookSpecItem.first] = hookSpecItem.second.get_value<string>();
    }
}

void JsonGraphParser :: addHooksProperties(Graph &graph, const ptree &root) {

    ptree hooksPropertiesSpec = root.get_child_optional(HOOKS_PROPERTIES).value_or(empty_ptree);
    for(auto hookSpecItem : hooksPropertiesSpec) {
        addHookProperties(graph, hookSpecItem.second, hookSpecItem.first);
    }

}



