#ifndef YAML_GRAPH_PARSER_H

#define YAML_GRAPH_PARSER_H

#include "../GraphParser.h"
#include <yaml-cpp/parser.h>
#include <yaml-cpp/yaml.h>

using namespace PatternCapture;

namespace PatternCapture {
    class YamlGraphParser : public GraphParser {
        private:
            void addGraphProperties(Graph &graph, const YAML::Node &);
            void addHookProperties(Graph &, const YAML::Node &, const string hookName);
            void addAllHooksProperties(Graph &, const YAML::Node &);
            Node* addNodeFrom(const YAML::Node &node, Node *comesFrom, Graph &graph);
            
        public:
            Graph* parse(const char *);
    };
};

#endif

