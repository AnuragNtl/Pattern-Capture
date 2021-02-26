#ifndef JSON_PICKER_TRANSFORM_H

#define JSON_PICKER_TRANSFORM_H

#include "../../nlohmann/json.hpp"
#include "../Transform.h"
#include "../../CommonUtils.h"

using namespace PatternCapture;

class JsonPickerTransform : public Transform<string, string> {
    public:
        string getId() const;
        string transform(string input, map<string, string> inputParams) const;
};

DEPENDENCY_DECLARATION

#endif

