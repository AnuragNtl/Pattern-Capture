#include "./ToJsonPickerTransform.h"

string ToJsonPickerTransform :: transform(StringSerializable input, map<string, string> params) const {
    string data = JsonPickerTransform::transform(ToJsonTransform::transform(input, params), params);
    return data;
}

string ToJsonPickerTransform :: getId() const {
    return "toJsonPicker";
}

Dependency* getDependency(const char *) {

    return new ToJsonPickerTransform;
}

vector<string> getDependencyTypes() {
    return {"transform"};
}

void* ToJsonPickerTransform :: operator()(void *input, map<string, string> inputParams) {
    return Transform<StringSerializable, string>::operator()(input, inputParams);
}




