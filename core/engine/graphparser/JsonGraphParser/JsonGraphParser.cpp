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



Graph* JsonGraphParser :: parse(const char *input) {
   
    ptree graphSpec;
    string inputData = input;
    
    istringstream graphSpecInput(inputData);
    
    try {
        Graph *graph = new Graph;
        read_json(graphSpecInput, graphSpec);
        for(auto &hook : graphSpec.get_child(GRAPH_HOOKS)) {

            graph->hooks.insert(hook.second.get_value<string>());
        }
        addNodeFrom(graphSpec, NULL, *graph); return graph; } catch(boost::exception &e) { throw GraphParseException("Cannot parse graph from JSON specified" + boost::diagnostic_information(e)); } }


Node* JsonGraphParser :: addNodeFrom(ptree node, Node *comesFrom, Graph &graph) {
    string nodeId = node.get_child(NODE_ID).get_value<string>();
    string type = node.get_child(NODE_TYPE).get_value<string>();
    string dependencyId = node.get_child(NODE_DEPENDENCY_ID).get_value<string>();
    ptree deliversToNodes = node.get_child(NODE_DELIVERS_TO);
    ptree acceptsFromNodesSpec = node.get_child(NODE_ACCEPTS_FROM);
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

    for(auto inputParamSpec : node.get_child(NODE_INPUT_PARAMS)) {

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

