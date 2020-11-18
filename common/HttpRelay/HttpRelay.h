#ifndef HTTP_RELAY

#define HTTP_RELAY

#include "../Common.h"
#include "../../core/engine/hooks/Hooks.h"
#include <map>
#include <boost/beast/http.hpp>

namespace PatternCapture {

    class HttpRelayDependency : public CommonDependency<string, string>, public Hook  {

        private:
            string host, path, url, method, payload;
            map<string, string> headers;
            HookType hookType;
            boost::beast::http::verb verb;

        protected:
            string getResponse() const;
            string extractRegex(string, string);
        public:
            HttpRelayDependency(string url, string method, string payload, map<string, string> headers, HookType hookType, boost::beast::http::verb);
            string getOutput(string input, map<string, string>);
            void executeHook(const Node &);
            HookType getHookType();
    };
};


#endif

