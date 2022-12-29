#include <iostream>
#include <boost/process.hpp>
#include <boost/asio.hpp>
#include <chrono>
#include "CommandLine.h"
#include "../../CommonUtils.h"

using namespace PatternCapture;
using namespace std;
using namespace boost::process;
using namespace boost::asio;


string CommandLine :: getOutput(string input, map<string, string> inputParams) const {
    cout << "Command Input : " << input << "\n";
    if (inputParams.find("command") == inputParams.end()) {
        throw std::exception();
    }
    CommandOutput *output = getCommandOutput(input.c_str(), input.size(), inputParams["command"]);
    if (output->outputLen > 0) {
        cout << "Output " << string(output->output) << "\n";
        return string(output->output, output->outputLen);
    }
    else if (output->errorLen > 0)  return string(output->error);
    else return string();
}

string CommandLine :: getId() const {
    return "commandLine";
}

vector<string> getDependencyTypes() {

    return {"captureAndTransformString"};

}

Dependency* getDependency(const char *dependencyName) {
    
    return new CommandLine;
}




