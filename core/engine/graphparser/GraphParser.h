#ifndef GRAPH_PARSER_H

#define GRAPH_PARSER_H

#include <string>
#include <vector>
#include <map>
#include <set>

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
      vector<string> inputParams;
      Node(string, string, string, set<Node*>, vector<string> inputParams, bool isRoot = false); //Not accepting deliversToNodes
      void addDeliversToNode(Node *);
      void removeFromAcceptsFromList(Node *);
      void removeFromDeliversToList(Node *);
      ~Node();
    };
    struct Graph {
      private:
        map<string, Node *> nodeIdWiseMap;
        set<Node *> rootNodes;
      public:
        Graph();
        ~Graph();
        void addNode(string, string, string, set<string> acceptsFrom, vector<string> inputParams);
        void removeNode(string id);
        set<Node *> getAllRootNodes() const;
        Node& getNodeById(string id) const; 
    };
    class GraphParser {
    public:
      virtual Graph parse(char *input) = 0;
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

