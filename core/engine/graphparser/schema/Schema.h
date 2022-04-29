#ifndef SCHEMA_H

#define SCHEMA_H

#include <string>
#include <map>
#include <vector>
#include "../../../../StringSerializable.h"



using namespace std;

namespace PatternCapture {


    enum SchemaType {OBJECT, ARRAY, ENUM, PRIMITIVE, ANY_OF};

    enum PrimitiveSchemaDataType {STRING, NUMBER, BOOLEAN};

    class SchemaTypeData {

        private:
            SchemaTypeData();
            void initializeSchemaTypes();
            void initializePrimitiveSchemaTypes();
            void initialize();
            static SchemaTypeData *schemaTypeData;
            map<SchemaType, string> schemaType;
            map<PrimitiveSchemaDataType, string> primitiveSchemaType;
        public:
            string getName(const SchemaType &);
            string getName(const PrimitiveSchemaDataType &);
            static SchemaTypeData* getSchemaTypeData();
    };


    template<class E>
    class Schema {
        public:
        operator string();
        virtual E getEntity() const = 0;
        virtual ~Schema() { }
    };

    template<class E>
    struct AnyOf : public Schema<E> {
        vector<Schema<E> *> anyOf;
    };

    template<class E>
    struct PrimitiveTypeSchema : public Schema<E> {
        PrimitiveSchemaDataType type;
        static PrimitiveTypeSchema* of(PrimitiveSchemaDataType type);
    };

    template<class E>
    struct EnumTypeSchema : public Schema<E> {
        vector<string> _enum;
    };

    template<class E>
    struct ObjectSchema : public Schema<E> {
        map<string, Schema<E> *> properties;
        string description;
    };

    template<class E>
    struct ArraySchema : public Schema<E> {
        vector<Schema<E> *> items;
    };

    template<class T>
    Schema<T> :: operator string() {
        return (string)getEntity();
    }

    template<class T>
    extern string getSchemaName(const T &schemaType) {
        return SchemaTypeData::getSchemaTypeData()->getName(schemaType);
    }

    
};


#endif


