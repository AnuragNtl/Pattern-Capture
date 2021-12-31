#ifndef HTTP_RELAY

#define HTTP_RELAY

#include "../Common.h"
#include "../../core/engine/hooks/Hooks.h"
#include <map>
#include <boost/beast/http.hpp>

#define URL_KEY "url"
#define HOST_KEY "host"
#define PORT_KEY "port"
#define PATH_KEY "path"
#define VERB_KEY "VERB"
#define PAYLOAD_KEY "payload"
#define HEADERS_KEY "headers"
#define HOOK_TYPE_KEY "hookType"
#define HEADER_DELIMITER "\n"
#define HEADER_NAME_VALUE_DELIMITER ":"
#define DEFAULT_PORT "80"

namespace PatternCapture {


    class HttpRelayDependency : public CommonDependency<string, string> {

        private:
            string host, port, path, url, payload;
            map<string, string> headers;
            boost::beast::http::verb verb;

        protected:
            string getResponse() const;
            string extractRegex(string, string);
            void loadParams(std::map<std::string, std::string> &);
            static map<string, http::verb> httpVerbMap;
            static void initializeVerbMap();
            void extractHostPortPathFromUrl(string);
        public:
            HttpRelayDependency();
            HttpRelayDependency(string url, string payload, map<string, string> headers, boost::beast::http::verb);
            string getOutput(string input, map<string, string>) const;
            virtual string getId() const;
            friend class HttpRelayHook;
    };

    class HttpRelayHook : public Hook {

        private:
            HookType hookType;
        public:
            HookType getHookType();
            void executeHook(const HookData&);
            string getId() const;
    };

};

extern "C" {

    extern vector<string> getDependencyTypes();
    extern Dependency* getDependency(const char *);

}


#endif

