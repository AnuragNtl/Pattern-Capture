#include <iostream>
#include <boost/process.hpp>
#include <boost/asio.hpp>
#include "CommandLine.h"

using namespace PatternCapture;
using namespace std;
using namespace boost::process;
using namespace boost::asio;


string CommandLine :: getOutput(string input, map<string, string> inputParams) const {
    ipstream outputPipe, errorPipe;
    string command;
    if(inputParams.find("command") != inputParams.end()) {
        command = inputParams["command"];
    } else {
        throw std::exception();
    }
    boost::asio::io_service ios;
    boost::process::async_pipe inputPipe(ios);
    child process(command, std_in < inputPipe, std_out > outputPipe, std_err > errorPipe);
    async_write(inputPipe, buffer(input), [] (const boost::system::error_code &ec, std::size_t size) {});
    inputPipe.close();
    process.wait();
    cout << "::\n";
    string output(istreambuf_iterator<char>(outputPipe), {}), error(istreambuf_iterator<char>(errorPipe), {});
    cout << process.exit_code() << "\n";
    if(process.exit_code() != 0) {
        cout << "Error: \n";
        cout << error;
        throw std::exception();
    }
    cout << output << "\n";
    return output;
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




