#ifndef HTTP_RELAY

#define HTTP_RELAY

#include "../Common.h"
#include "../../core/engine/hooks/Hooks.h"

namespace PatternCapture {

    class HttpRelayDependency : public CommonDependency<string, string>, public Hook  {

        private:
            string url, method, payload;
            HookType hookType;
        protected:
            string getResponse() const;
        public:
            HttpRelayDependency(string url, string method, string payload, HookType hookType);
            string getOutput(string input, map<string, string>);
            void executeHook(const Node &);
            HookType getHookType();
    };
};


#endif

