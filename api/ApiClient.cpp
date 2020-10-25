#include "ApiClient.h"

using namespace PatternCapture;

void* ApiClient :: operator()(void *data) {
    map<string, string> *inputParams = (map<string, string> *)data;
    ptree *inputData = new ptree;
    return (*this)(inputData, *inputParams);
}

void* ApiClient :: operator()(void *input, map<string, string> params) {

    ptree *data = (ptree*)input;
    ptree *response = new ptree;
    *response = transfer(*data, params);
    return response;
}

ApiException :: ApiException(string message) : message(message) {}

const char* ApiException :: what() const noexcept {
    return message.c_str();
}


