#ifndef JSON_SERIALIZABLE_H

#define JSON_SERIALIZABLE_H

#include <iostream>
#include "./nlohmann/json.hpp"

#define TO_JSON NLOHMANN_DEFINE_TYPE_INTRUSIVE

#define TO_JSON_STRING(Type, ...) TO_JSON(Type, __VA_ARGS__) \
    operator string() const { \
        nlohmann::json data; \
        to_json(data, *this); \
        return data.dump(); \
    }

using namespace std;

namespace PatternCapture {

    class StringSerializable {
        protected:
            string data;
        public:
            StringSerializable() = default;
            StringSerializable(StringSerializable &other) { this->data = (string)other; }
            StringSerializable(const vector<StringSerializable> &);
            StringSerializable(const vector<String
            virtual operator string() const { return data; }
    };
        
};



#endif

