#ifndef JSON_SCHEMA_H

#define JSON_SCHEMA_H

#include "Schema.h"
#include "../../../../nlohmann/json.hpp"

using namespace nlohmann;

using namespace PatternCapture;

namespace PatternCapture {
    class JsonSchema : public ObjectSchema<json> {
        json getEntity() const;
    };

    json JsonSchema :: getEntity() {
        json
    }
};

#endif

