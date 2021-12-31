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
            StringSerializable(const StringSerializable &other) { this->data = (string)other; }
            virtual operator string() const { return data; }
    };

    /*template<class T>
    void to_json(nlohmann::json &data, const vector<T> &stringSerializables) {
        for(const auto &item : stringSerializables) {
            nlohmann::json itemData;
            to_json(itemData, item);
            data.push_back(itemData);
        }
    }*/

    template<class T>
    T loadJson(string raw) {
        nlohmann::json data = nlohmann::json::parse(raw);
        return data.get<T>();
    }
        
};



#endif

