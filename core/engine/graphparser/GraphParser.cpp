#include "GraphParser.h"
#include <algorithm>

namespace PatternCapture {

  Node :: Node(string id, string type, string dependencyId, set<Node *> acceptsFromNodes, vector<string> inputParams, bool isRoot) : id(id), type(type), dependencyId(dependencyId), acceptsFromNodes(acceptsFromNodes), isRoot(isRoot), inputParams(inputParams) {
    addAcceptsFromNodes();
  }

  void Node :: addAcceptsFromNodes() {
    for_each(acceptsFromNodes.begin(), acceptsFromNodes.end(), [this] (Node *acceptsFromNode) {
        acceptsFromNode->deliversToNodes.insert(this);
        });
  }


  Node :: ~Node() {
    for_each(acceptsFromNodes.begin(), acceptsFromNodes.end(), [] (Node *node) {
        delete node;
        });
    for_each(deliversToNodes.begin(), deliversToNodes.end(), [] (Node *node) {
        delete node;
        });
  }

  void Node :: addDeliversToNode(Node *node) {
    deliversToNodes.insert(node);
    node->acceptsFromNodes.insert(this);
  }

  void Node :: removeFromAcceptsFromList(Node *node) {
    node->deliversToNodes.erase(this);
    acceptsFromNodes.erase(node);
  }

  void Node :: removeFromDeliversToList(Node *node) {
    node->acceptsFromNodes.erase(this);
    deliversToNodes.erase(node);
  }

  Graph :: Graph() {

  }

  void Graph :: addNode(string id, string type, string dependencyId, set<string> acceptsFrom, vector<string> inputParams) {
   set<Node*> acceptsFromNodes;
    transform(acceptsFrom.begin(), acceptsFrom.end(), inserter(acceptsFromNodes, acceptsFromNodes.begin()), 
        [this] (string nodeId) {
        return nodeIdWiseMap[nodeId];
        });
    bool isRoot = acceptsFromNodes.size() == 0;
    Node *node = new Node(id, type, dependencyId, acceptsFromNodes, inputParams, isRoot);
    nodeIdWiseMap[id] = node;
    if(isRoot) {
      rootNodes.insert(node);
    }
  }

  void Graph :: removeNode(string id) {
    
    if(nodeIdWiseMap.find(id) == nodeIdWiseMap.end()) {
      throw GraphParseException("Node with id " + id + " not found");
    }
    Node *node = nodeIdWiseMap[id];
    if(rootNodes.find(node) != rootNodes.end()) {
      rootNodes.erase(node);
    }
    nodeIdWiseMap.erase(id);
    delete node;
  }

  set<Node *> Graph :: getAllRootNodes() const {
    return rootNodes;
  }
  
  Node& Graph :: getNodeById(string id) const {
    if(nodeIdWiseMap.find(id) == nodeIdWiseMap.end()) {
      throw new GraphParseException("Node with id " + id + " not found");
    }
    return *(nodeIdWiseMap.find(id)->second);
  }
};

