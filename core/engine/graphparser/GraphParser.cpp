#include "GraphParser.h"
#include <algorithm>

namespace PatternCapture {

  Node :: Node(string id, string type, string dependencyId, set<Node *> acceptsFromNodes, vector<string> inputParams, bool isRoot) : id(id), type(type), dependencyId(dependencyId), acceptsFromNodes(acceptsFromNodes), inputParams(inputParams), isRoot(isRoot) {
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
  }

  void Graph :: removeNode(Node *node) {
    
  }
};

