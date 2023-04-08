#include "CommonUtils.h"
#include <sys/stat.h>
#include <map>
#include <fstream>
#include <functional>
#include <boost/process.hpp>
#include <cstring>
#include <chrono>
#include <boost/asio.hpp>
#include <algorithm>

namespace PatternCapture {
  vector<string> listDirectory(string directory) { if(!is_directory(directory)) {
      throw exception();
    }
    vector<string> contents;
    path directoryPath(directory);
    for(auto it = directory_iterator(directoryPath); it != directory_iterator(); it++) {
      contents.push_back(it->path().filename().string());
    }
    return contents;
  }

#define BUF_LEN 1024

string getContents(istream &&in) {
    string data = "";
    char buffer[BUF_LEN];
    while(!in.eof()) {
        in.read(buffer, BUF_LEN - 1);
        int count = in.gcount();
        buffer[count] = '\0';
        data.append(string(buffer));
    }
        std::ifstream *file = dynamic_cast<std::ifstream*>(&in);
    if(file != NULL) {
        file->close();
    }
    return data;
}

string readLink(string path) {
    char *buf = new char[BUF_LEN];
    int status;
    status = readlink(path.c_str(), buf, BUF_LEN - 1);
    if(status) {
        buf[status] = '\0';
    } else {
        buf[0] = '\0';
    }
    string data = string(buf);
    delete[] buf;
    return data;

}

bool isNumeric(string data) {
    for(char item : data) {
        if(!std::isdigit(item)) {
            return false;
        }
    }
    return true;
}

bool pathExists(string path) {
    return exists(path);
}


CommandOutput :: CommandOutput(char *output, char *err, int errorLen, int outputLen) :
    output(output), error(err), errorLen(errorLen), outputLen(outputLen) { }

CommandOutput* getCommandOutput(const char *input, size_t inputSize, string command, bool binary) {
    boost::process::ipstream outputPipe, errorPipe;
    boost::asio::io_service ios;
    boost::process::async_pipe inputPipe(ios);
    boost::process::child process(command, boost::process::std_in < inputPipe, boost::process::std_out > outputPipe, boost::process::std_err > errorPipe);
    async_write(inputPipe, boost::asio::buffer(input, inputSize * sizeof(const char)), [] (const boost::system::error_code &ec, std::size_t size) {});
    inputPipe.close();
    process.wait();
    cout << "::\n";
    vector<char> output(istreambuf_iterator<char>(outputPipe), {}), error(istreambuf_iterator<char>(errorPipe), {});
    char *outputData = new char[output.size() + 1];
    char *errorData = new char[error.size() + 1];
    memcpy(outputData, output.data(), output.size());
    memcpy(errorData, error.data(), error.size());
    if (binary) {
        outputData[output.size()] = '\0';
        errorData[error.size()] = '\0';
    }
    cout << string(outputData);
    if(process.exit_code() != 0) {
        cout << "Error: \n";
        cout << errorData;
        throw std::exception();
    }

    return new CommandOutput(outputData, errorData, error.size(), output.size());
}

void BinData :: assign(std::string details) {
    cout << "BinData::\n";
    const char *content = details.c_str();
    this->data = new char[details.size() + 1];
    this->length = details.size();
    memcpy(this->data, content, this->length * sizeof(char));
}

BinData :: BinData() { }

BinData :: BinData(std::string details) {
    assign(details);
}

BinData& BinData :: operator=(std::string details) {
    assign(details);
    return *this;
}

BinData :: operator std::string() {
    data[this->length] = '\0';
    return std::string(data);
}
};


