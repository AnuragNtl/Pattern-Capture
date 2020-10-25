#include <iostream>
#include "ApiClientJava.h"
#include "jniApiClient.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

using namespace std;
using namespace PatternCapture;
using namespace boost::property_tree;

#define NODE_CLASS_KEY "nodeClass"

ptree ApiClientJava :: transfer(ptree input, map<string, string> properties) {

    JavaCPP_init(0, NULL);
    cout << "Initialized\n";
    string s = "1234";
    if(properties.find(NODE_CLASS_KEY) == properties.end()) {
        throw ApiException("nodeClass Not present");
    }
    for(map<string, string> :: iterator inputIterator = properties.begin(); inputIterator != properties.end(); inputIterator++) {
        input.put(inputIterator->first, inputIterator->second);
    }
    ostringstream buf;
    write_json(buf, input, false);
    cout << "Calling dependencyNode with data " <<  buf.str() << "\n";
    string relayData = buf.str();
    string responseData = call(relayData);
    istringstream responseStream(responseData);
    ptree response;
    read_json(responseStream, response);
    return response;
}

string ApiClientJava :: getId() const {
    return "api";
}


vector<string> getDependencyTypes() {

    return {"capture"};

}

Dependency* getDependency(string) {

    return new ApiClientJava;
}



