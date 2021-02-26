#ifndef TO_JSON_TRANSFORM_H

#define TO_JSON_TRANSFORM_H

#include "../Transform.h"
#include "../../StringSerializable.h"

using namespace PatternCapture;

class ToJsonTransform : public Transform<StringSerializable, string> {
    public:
        string getId() const;
        string transform(StringSerializable, map<string, string>) const;
};

extern "C" {
    extern Dependency* getDependency(const char *);
    extern vector<string> getDependencyTypes();
}

#endif

