#include "JsonSchema.h"

namespace PatternCapture {

    JsonNode JsonNode :: wrap(json node) {
        JsonNode schemaNode;
        schemaNode.data = node;
        return schemaNode;
    }

    JsonNode JsonAnyOf :: getEntity() const {
        json schema;
        json anyOf;
        for(const auto &item : this->anyOf) {
            anyOf.push_back(item->getEntity().data);
        }
        schema[SCHEMA_ANY_OF] = anyOf;
        return JsonNode::wrap(schema);
    }


    JsonNode JsonObjectSchema :: getEntity() const {

        json schema;

        schema[SCHEMA_TYPE] = getSchemaName(SchemaType::OBJECT);

        json properties;

        for(const auto &propertyPair : this->properties) {
            properties[propertyPair.first] = propertyPair.second->getEntity().data;
        }
        schema[SCHEMA_PROPERTIES] = properties;

        return JsonNode::wrap(schema);
    }

    JsonNode JsonPrimitiveTypeSchema :: getEntity() const {
        json schema;
        schema[SCHEMA_TYPE] = getSchemaName(type);
        return JsonNode::wrap(schema);
    }

    JsonNode JsonEnumTypeSchema :: getEntity() const {
        json schema;
        schema[SCHEMA_TYPE] = getSchemaName(PrimitiveSchemaDataType::STRING);
        json enumEntries;
        for(const string &item : _enum) {
            enumEntries.push_back(item);
        }
        schema[SCHEMA_ENUM] = enumEntries;
        return JsonNode::wrap(schema);
    }

    JsonNode JsonArraySchema :: getEntity() const {
        json schema;
        schema[SCHEMA_TYPE] = getSchemaName(SchemaType::ARRAY);
        json items;
        for(const auto &item : this->items) {
            items.push_back(item->getEntity().data);
        }
        items[SCHEMA_ITEMS] = items;
        return JsonNode::wrap(schema);
    }

    JsonNode :: operator string() {
        return data.dump();
    }

};

