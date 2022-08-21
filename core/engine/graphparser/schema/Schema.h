#ifndef SCHEMA_H

#define SCHEMA_H

#include <string>
#include <map>
#include <vector>
#include <initializer_list>
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
        AnyOf<E>& withOption(Schema<E> &);
        virtual ~AnyOf();
    };

    template<class E>
    struct PrimitiveTypeSchema : public Schema<E> {
        PrimitiveSchemaDataType type;
    };

    template<class E>
    struct EnumTypeSchema : public Schema<E> {
        vector<string> _enum;
        EnumTypeSchema() = default;
        EnumTypeSchema(initializer_list<string>);
        EnumTypeSchema<E>& operator<<(string item) {
            _enum.push_back(item);
            return *this;
        }
    };

    template<class E>
    struct ObjectSchema : public Schema<E> {
        map<string, Schema<E> *> properties;
        virtual ~ObjectSchema();
        string description;
        Schema<E>*& operator[](string key);
        string ref;
    };

    template<class E>
    struct ArraySchema : public Schema<E> {
        Schema<E> *items;
        string ref;
        virtual ~ArraySchema();
    };

    template<class T>
    Schema<T> :: operator string() {
        return (string)getEntity();
    }

    template<class T>
    extern string getSchemaName(const T &schemaType) {
        return SchemaTypeData::getSchemaTypeData()->getName(schemaType);
    }

    template<class T>
    Schema<T>*& ObjectSchema<T> :: operator[](string key) {
        return this->properties[key];
    }

    
    template<class E>
        ArraySchema<E> :: ~ArraySchema() {
            delete items;
        }

    template<class E>
    EnumTypeSchema<E> :: EnumTypeSchema(initializer_list<string> items) {
        for(string item : items) {
            _enum.push_back(item);
        }
    }

    template<class E>
        AnyOf<E> :: ~AnyOf() {
            for(Schema<E> *&schema : anyOf) {
                delete schema;
            }
        }

    template<class E>
        ObjectSchema<E> :: ~ObjectSchema() {
            for(auto &pair : properties) {
                delete pair.second;
            }
        }
    

};


#endif


