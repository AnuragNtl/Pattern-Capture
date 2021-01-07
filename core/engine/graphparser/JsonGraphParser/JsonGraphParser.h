#ifndef JSON_GRAPH_PARSER_H
#define JSON_GRAPH_PARSER_H

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "../GraphParser.h"

#define NODE_ID "id"
#define NODE_TYPE "type"
#define NODE_DEPENDENCY_ID "dependencyId"
#define NODE_DELIVERS_TO "deliversToNodes"
#define NODE_ACCEPTS_FROM "acceptsFromNodes"
#define NODE_INPUT_PARAMS "inputParams"
#define GRAPH_PROPERTIES "graphProperties"
#define HOOKS_PROPERTIES "hooksProperties"

using namespace boost::property_tree;

namespace PatternCapture {

    class JsonGraphParser : public GraphParser {

        private:
            Node* addNodeFrom(ptree node, Node *comesFrom, Graph &graph);
            void addGraphProperties(Graph &, const ptree &);
            void addHookProperties(Graph &, const ptree &, string hookName);
            void addHooksProperties(Graph &, const ptree &);

        public:
            Graph* parse(const char *input);
    };
};

#endif

