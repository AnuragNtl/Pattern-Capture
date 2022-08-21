#ifndef JSON_SCHEMA_H

#define JSON_SCHEMA_H

#include "Schema.h"
#include "../../../../nlohmann/json.hpp"
#include <functional>
#include <algorithm>

#define SCHEMA_TYPE "type"
#define SCHEMA_PROPERTIES "properties"
#define SCHEMA_ANY_OF "anyOf"
#define SCHEMA_ENUM "enum"
#define SCHEMA_ITEMS "items"
#define SCHEMA_REF "$ref"

using namespace std;

using namespace nlohmann;

using namespace PatternCapture;

namespace PatternCapture {

    struct JsonNode {
        json data;
        operator string();
        static JsonNode wrap(json node);
    };

    class JsonObjectSchema : public ObjectSchema<JsonNode> {
        public:
        JsonNode getEntity() const;
    };

    class JsonAnyOf : public AnyOf<JsonNode> {
        public:
            JsonNode getEntity() const;
    };

    class JsonPrimitiveTypeSchema :  public PrimitiveTypeSchema<JsonNode> {
        public:
            JsonNode getEntity() const;
    };

    class JsonEnumTypeSchema : public EnumTypeSchema<JsonNode> {
        public:
            JsonEnumTypeSchema() = default;
            JsonEnumTypeSchema(initializer_list<string>);
            JsonNode getEntity() const;
    };

    class JsonArraySchema : public ArraySchema<JsonNode> {
        public:
            JsonNode getEntity() const;
    };


};

#endif

