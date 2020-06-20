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
#define GRAPH_HOOKS "hooks"

using namespace boost::property_tree;

namespace PatternCapture {

    class JsonGraphParser : public GraphParser {

        private:
            Node* addNodeFrom(ptree node, Node *comesFrom, Graph &graph);
        public:
            Graph* parse(char *input);
    };
};

#endif

