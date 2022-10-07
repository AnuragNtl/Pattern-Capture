#ifndef SCHEMA_PROPERTIES_H

#define SCHEMA_PROPERTIES_H

#include "Schema.h"
#include "JsonSchema.h"

using namespace PatternCapture;


namespace PatternCapture {

    typedef JsonObjectSchema ObjectProperties;
    typedef JsonObjectSchema SchemaProperties;
    typedef JsonAnyOf AnyOfProperties;
    typedef JsonPrimitiveTypeSchema PrimitiveTypeProperties;
    typedef JsonEnumTypeSchema EnumTypeProperties;
    typedef JsonArraySchema ArrayTypeProperties;
    typedef JsonNode SchemaContent;
};


#endif

