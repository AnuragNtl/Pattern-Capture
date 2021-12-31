#ifndef JSON_PICKER_TRANSFORM_H

#define JSON_PICKER_TRANSFORM_H

#include "../../nlohmann/json.hpp"
#include "../Transform.h"
#include "../../CommonUtils.h"

using namespace PatternCapture;

class JsonPickerTransform : public virtual Transform<string, string> {
    public:
        virtual string getId() const;
        virtual string transform(string input, map<string, string> inputParams) const;
};

DEPENDENCY_DECLARATION

#endif

