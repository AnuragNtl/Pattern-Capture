#ifndef GRAPH_PARSER_H

#define GRAPH_PARSER_H

#include <string>
#include <vector>
#include <map>
#include <set>
#include <Dependencies.h>

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
      void addDeliversToNode(Node *);
      void removeFromAcceptsFromList(Node *);
      void removeFromDeliversToList(Node *);
      Dependency *dependency;
      ~Node();
    };
    struct Graph {
      private:
        map<string, Node *> nodeIdWiseMap;
      public:
        set<Node *> rootNodes;
        set<string> hooks;
        Graph();
        ~Graph();
        Node* addNode(string, string, string, set<string> acceptsFrom, map<string, string> inputParams);
        void removeNode(string id);
        set<Node *> getAllRootNodes() const;
        Node& getNodeById(string id) const; 
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
  };

#endif

