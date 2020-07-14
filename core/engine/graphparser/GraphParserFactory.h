#ifndef GRAPH_PARSER_FACTORY_H

#define GRAPH_PARSER_FACTORY_H

#include "GraphParser.h"

using namespace PatternCapture;

class GraphParserFactory {

    private:
        map<string, GraphParser*> parsers;
    public:
        static const string GRAPH_PARSER_JSON;
        GraphParserFactory();
        GraphParser* getGraphParser(string);
        ~GraphParserFactory();
};

#endif

