#include <iostream>
#include "JsonGraphParser.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <vector>
#include <set>

using namespace std;
using namespace PatternCapture;
using namespace boost::property_tree;



Graph JsonGraphParser :: parse(char *input) {
   
    ptree graphSpec;
    string inputData = input;
    
    istringstream graphSpecInput;
    
    try {
        Graph graph;
        read_json(graphSpecInput, graphSpec);
        
        return graph;
    } catch(boost::exception &e) {
        throw GraphParseExcepton("Cannot parse graph from JSON specified");
    }
}


Node* JsonGraphParser :: addNodeFrom(ptree node, Node *comesFrom, Graph &graph) {

    string nodeId = node.get_value<string>(NODE_ID);
    string type = node.get_value(NODE_TYPE);
    string dependencyId = node.get_value(NODE_DEPENDENCY_ID);
    ptree deliversToNodes = node.get_child(NODE_DELIVERS_TO);
    ptree acceptsFromNodesSpec = node.get_child(NODE_ACCEPTS_FROM);
    set<string> acceptsFromNodes;
    acceptsFromNodes.insert(comesFrom->id);

    vector<string> inputParams;

    for(auto &acceptsFromNode : acceptsFromNodesSpec) {
        acceptsFromNodes.insert(acceptsFromNode.second.get_value<string>());
    }
    
    for(auto inputParamSpec : node.get_child(NODE_INPUT_PARAMS)) {

            inputParams.push_back(inputParamSpec.second.get_value<string>());
            }
    
    Node *graphNode = graph.addNode(nodeId, type, dependencyId, acceptsFromNodes, inputParams);
    for(auto &deliversToNode : deliversToNodes) {
        Node *deliversToGraphNode = addNodeFrom(deliversToNode.second, graphNode, graph);
        graphNode->addDeliversToNode(deliversToGraphNode);
    }
    return graphNode;
}

