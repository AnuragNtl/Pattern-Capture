#ifndef API_CLIENT_H

#define API_CLIENT_H

#include <map>
#include <boost/property_tree/ptree.hpp>
#include <string>
#include "../Dependencies.h"

using namespace std;
using namespace boost::property_tree;
using namespace PatternCapture;

namespace PatternCapture {
    class ApiClient : public Dependency {
        public:
            virtual string getId() const = 0;
            void* operator()(void *input, map<string, string> params);
            void* operator()(void *);
            virtual ptree transfer(ptree input, map<string, string> properties) { return ptree(); }
    };

    class ApiException {
        private:
            string message;
        public:
            ApiException(string);
            const char* what() const noexcept;
    };
};

#endif

