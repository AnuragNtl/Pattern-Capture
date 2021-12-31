#include "JsonPickerTransform.h"
#include "../../nlohmann/json.hpp"

using nlohmann::json;

string JsonPickerTransform :: getId() const {
    return "jsonPicker";
}

string JsonPickerTransform :: transform(string input, map<string, string> inputParams) const {
    json data = json::parse(input);
    if(inputParams["key"] == "*") {
        return data.dump();
    } else {
        if(data.is_array()) {
            int key = stoi(inputParams["key"]);
            return data[key].dump();
        } else {
            return data[inputParams["key"]].dump();
        }
    }
}

Dependency* getDependency(const char *) {
    return new JsonPickerTransform;
}

vector<string> getDependencyTypes() {
    return {"transform"};
}



