#ifndef JSON_SERIALIZABLE_H

#define JSON_SERIALIZABLE_H

#include <iostream>

using namespace std;

namespace PatternCapture {

    class StringSerializable {
        private:
            string data;
        public:
            StringSerializable() = default;
            StringSerializable(StringSerializable &other) { this->data = (string)other; }
            virtual operator string() const { return data; }
    };
        
};



#endif

