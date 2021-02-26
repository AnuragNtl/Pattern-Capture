#include "GraphParserFactory.h"
#include "JsonGraphParser/JsonGraphParser.h"
#include "YamlGraphParser/YamlGraphParser.h"

using namespace PatternCapture;

GraphParserFactory :: GraphParserFactory() {
    parsers[GRAPH_PARSER_JSON] = new JsonGraphParser();
    parsers[GRAPH_PARSER_YAML] = new YamlGraphParser
        ;
}

GraphParser* GraphParserFactory ::  getGraphParser(string parserName) {
    if(parsers.find(parserName) == parsers.end()) {

        throw  GraphParseException("No graph parser " + parserName + " found");
    }
    return parsers[parserName];
}

GraphParserFactory :: ~GraphParserFactory() {

    for(auto &parserPair : parsers) {
        delete parserPair.second;
    }
}

const string GraphParserFactory :: GRAPH_PARSER_JSON = "graphParserJson";
const string GraphParserFactory :: GRAPH_PARSER_YAML = "graphParserYaml";

