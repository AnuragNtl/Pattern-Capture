#ifndef TO_JSON_PICKER_TRANSFORM_H

#define TO_JSON_PICKER_TRANSFORM_H

#include "../../CommonUtils.h"
#include "../ToJsonTransform/ToJsonTransform.h"
#include "../JsonPickerTransform/JsonPickerTransform.h"

using namespace PatternCapture;

class ToJsonPickerTransform : public ToJsonTransform, JsonPickerTransform {
    public:
        string getId() const;
        string transform(StringSerializable, map<string, string>) const;
        void* operator()(void* , map<string, string>);
};

DEPENDENCY_DECLARATION

#endif

