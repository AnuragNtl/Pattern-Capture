#include "Schema.h"

namespace PatternCapture {

    SchemaTypeData :: SchemaTypeData() {
        initialize();
    }

    void SchemaTypeData :: initialize() {
        initializeSchemaTypes();
        initializePrimitiveSchemaTypes();
    }

    void SchemaTypeData :: initializeSchemaTypes() {
        const char *schemaTypeValues[] = {"object", "array", "string", "string", "anyOf"};
        SchemaType schemaTypes[] = {OBJECT, ARRAY, ENUM, PRIMITIVE, ANY_OF};
        for(int i = 0; i < 5; i++) {
            this->schemaType[schemaTypes[i]] = schemaTypeValues[i];
        }
    }

    void SchemaTypeData :: initializePrimitiveSchemaTypes() {
        const char *primitiveTypeValues[] = {"string", "number", "boolean"};
        PrimitiveSchemaDataType primitiveTypes[] = {STRING, NUMBER, BOOLEAN};
        for(int i = 0; i < 3; i++) {
            primitiveSchemaType[primitiveTypes[i]] = primitiveTypeValues[i];
        }
    }

    SchemaTypeData* SchemaTypeData :: getSchemaTypeData() {
        if(SchemaTypeData::schemaTypeData == NULL) {
            SchemaTypeData::schemaTypeData = new SchemaTypeData;
        }
        return schemaTypeData;
    }

    SchemaTypeData* SchemaTypeData :: schemaTypeData = NULL;

    string SchemaTypeData :: getName(const SchemaType &schemaType) {
        return schemaTypeData->schemaType[schemaType];
    }

    string SchemaTypeData :: getName(const PrimitiveSchemaDataType &primitiveSchemaType) {
        return schemaTypeData->primitiveSchemaType[primitiveSchemaType];
    }

    template<class E>
    PrimitiveTypeSchema* PrimitiveTypeSchema<E> :: of(PrimitiveSchemaDataType type) {
        PrimitiveTypeSchema<E> *schema = new PrimitiveTypeSchema<E>;
        schema->type = type;
        return schema;
    }
};

