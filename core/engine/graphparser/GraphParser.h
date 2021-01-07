#ifndef GRAPH_PARSER_H

#define GRAPH_PARSER_H

#include <string>
#include <vector>
#include <map>
#include <set>
#include <Dependencies.h>
#include <iostream>

#define NATIVE_ENGINE "nativeEngine"

#define DEFAULT_ENGINE NATIVE_ENGINE

using namespace std;

  namespace PatternCapture {
    
    struct Node  {
      private:
        void addAcceptsFromNodes();
      public:
      string id;
      string type;
      string dependencyId;
      set<Node *> deliversToNodes;
      set<Node *> acceptsFromNodes;
      bool isRoot;
      map<string, string> inputParams;
      string executeWithEngine;
      Node(string, string, string, set<Node*>, map<string, string> inputParams, bool isRoot = false, string executeWithEngine = DEFAULT_ENGINE); //Not accepting deliversToNodes
      Node() = default;
      void addDeliversToNode(Node *);
      void removeFromAcceptsFromList(Node *);
      void removeFromDeliversToList(Node *);
      Dependency *dependency;
      ~Node();
    };

    struct HookProperties {
        
        map<string, string> properties;
        string& operator[](string);
        friend ostream& operator<<(ostream &out, const HookProperties &);
    };

    struct Graph {
      private:
        map<string, Node *> nodeIdWiseMap;
      public:
        map<string, HookProperties > hookProperties;
        set<Node *> rootNodes;
        map<string, string> properties;
        Graph();
        ~Graph();
        Node* addNode(string, string, string, set<string> acceptsFrom, map<string, string> inputParams);
        void removeNode(string id);
        set<Node *> getAllRootNodes() const;
        Node& getNodeById(string id) const; 
        operator string();
        string toString();
        HookProperties& operator[](string);
    };
    class GraphParser {
    public:
      virtual Graph* parse(const char *input) = 0;
      virtual ~GraphParser() {}
    };

    class GraphParseException : public exception {
      private:
        string message;
      public:
        GraphParseException(string message) {
          this->message = message;
        }
        const char *what() const noexcept {
          return message.c_str(); 
        }
    };
    ostream& operator<<(ostream &out, const Graph &graph);
    ostream& operator<<(ostream &out, const Node &node);
    ostream& operator<<(ostream &out, const HookProperties &);
    
  };

#endif

