#ifndef TO_JSON_TRANSFORM_H

#define TO_JSON_TRANSFORM_H

#include "../Transform.h"
#include "../../StringSerializable.h"

using namespace PatternCapture;

class ToJsonTransform : public virtual Transform<StringSerializable, string> {
    public:
        virtual string getId() const;
        virtual string transform(StringSerializable, map<string, string>) const;
};

extern "C" {
    extern Dependency* getDependency(const char *);
    extern vector<string> getDependencyTypes();
}

#endif

