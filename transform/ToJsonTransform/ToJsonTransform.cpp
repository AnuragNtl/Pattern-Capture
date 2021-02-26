#include "ToJsonTransform.h"

string ToJsonTransform :: getId() const {
    return "toJson";
}

string ToJsonTransform :: transform(StringSerializable stringSerializable, map<string, string> inputParams) const {
    string data = (string)stringSerializable;
    cout << "Transformed data " << data << "\n";
    return data;
}

Dependency * getDependency(const char *dependencyName) {
    return new ToJsonTransform;
}

vector<string> getDependencyTypes() {

    return {"transform"};
}





