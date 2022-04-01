#include "./GraphParser.h"
#include <algorithm>
#include <sstream>
#include <boost/algorithm/string.hpp>
#include "GraphPropertyHooks.h"

using namespace boost;

namespace PatternCapture {


  Node :: Node(string id, string type, string dependencyId, set<Node *> acceptsFromNodes, map<string, string> inputParams, bool isRoot, string executeWithEngine) : id(id), type(type), dependencyId(dependencyId), acceptsFromNodes(acceptsFromNodes),  inputParams(inputParams), executeWithEngine(executeWithEngine), dependency(NULL) {
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
        delete node; });
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

  Graph :: Graph() : repeatTimes(1) {
      this->repeatType = ONCE;
  }

  Node* Graph :: addNode(string id, string type, string dependencyId, set<string> acceptsFrom, map<string, string> inputParams) {
   set<Node*> acceptsFromNodes;
    transform(acceptsFrom.begin(), acceptsFrom.end(), inserter(acceptsFromNodes, acceptsFromNodes.begin()), 
        [this, dependencyId] (string nodeId) {
        return nodeIdWiseMap[nodeId];
        });
    bool isRoot = acceptsFromNodes.size() == 0;
    Node *node = new Node(id, type, dependencyId, acceptsFromNodes, inputParams, isRoot);
    nodeIdWiseMap[id] = node;
    if(isRoot) {
      rootNodes.insert(node);
    }
    return node;
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
      throw GraphParseException("Node with id " + id + " not found");
    }
    return *(nodeIdWiseMap.find(id)->second);
  }

  Graph :: ~Graph() {
      for(auto node : rootNodes) {

          delete node;
      }
  }

  ostream& operator<<(ostream &out, const Graph &graph) {

      out << "---------------Graph----------------\n";
      out << "Hooks:\n";
      for(const auto &hookPropertiesPair : graph.hookProperties) {
          out << hookPropertiesPair.first << "\n";
          out << hookPropertiesPair.second;
      }
      out << "Graph Properties : \n";
      for(const auto &graphPropertyPair : graph.properties) {

          out << graphPropertyPair.first << " : " << graphPropertyPair.second << "\n";
      }
      out << "Details : \n";
      out << "repeatType : " << graph.repeatType << "\n";
      out << "repeatTimes : " << graph.repeatTimes << "\n";
      for(const Node *node : graph.rootNodes) {
          out << *node;
      }
      return out;
  }

  ostream& operator<<(ostream &out, const Node &node) {
      out << "--------------Node-----------------\n";
      out << "id " << node.id << "\n";
      out << "type " << node.type << "\n";
      out << "dependencyId " << node.dependencyId << "\n";
      for(Node *connectedNode : node.acceptsFromNodes) {
          out << "Accepts from: " << connectedNode->id << "\n";
      }
      for(Node *connectedNode : node.deliversToNodes) {
          std::ostringstream paddedOutput;
          out << "\n" << node.id << " delivers to: \n"; 
          paddedOutput << *connectedNode << "\n";
          string output = paddedOutput.str();
          replace_all(output, "\n", "\n    ");
          out << output;
      }
      return out;
  }

  Graph :: operator string() {
      ostringstream output;
      output << (*this);
      return output.str();
  }

  string Graph :: toString() {

      return (string)(*this);
  }

  HookProperties& Graph :: operator[](string key) {
      return hookProperties[key];
  }

  string& HookProperties :: operator[](string key) {
      return properties[key];
  }

  ostream& operator<<(ostream &out, const HookProperties &hookProperties) {
      for(const auto &hookPropertyPair : hookProperties.properties)
          out << "    " << hookPropertyPair.first << " " << hookPropertyPair.second << "\n";
      return out;
  }
  
  void Graph :: addProperty(string name, string value) {
      properties[name] = value;
      for(const auto *propertyHook : GRAPH_PROPERTY_HOOKS) {
          (*propertyHook)(*this, properties);
      }
  }


  bool HookProperties :: hasProperty(string id) const {
      return properties.find(id) != properties.end();
  }

  SchemaProperties generateSchemaProperties(const Graph &graph) {
      SchemaProperties schemaProperties;
      for(const auto &pair : dependencyTypeWiseTable) {
          Dependency *dependency = pair.second;
          set<string> requiredParameters = dependency->getRequiredParameters();
          requiredParameters
          
      }
      return SchemaProperties();
  }


  
};

