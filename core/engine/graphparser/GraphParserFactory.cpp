#include "GraphParserFactory.h"
#include "JsonGraphParser/JsonGraphParser.h"

using namespace PatternCapture;

GraphParserFactory :: GraphParserFactory() {
    parsers[GRAPH_PARSER_JSON] = new JsonGraphParser();
}

GraphParser* GraphParserFactory ::  getGraphParser(string parserName) {
    if(parsers.find(parserName) == parsers.end()) {

        throw  GraphParseException("No graph parser " + parserName + " found");
    }
    return parsers[GRAPH_PARSER_JSON];
}

GraphParserFactory :: ~GraphParserFactory() {

    for(auto &parserPair : parsers) {
        delete parserPair.second;
    }
}

const string GraphParserFactory :: GRAPH_PARSER_JSON = "graphParserJson";

