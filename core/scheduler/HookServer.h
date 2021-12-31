#ifndef HOOK_SERVER_H

#define HOOK_SERVER_H

#include <vector>
#include <map>


#include "../../StringSerializable.h"
#include "../engine/hooks/Hooks.h"
#include "./Scheduler.h"

using namespace std;
using namespace PatternCapture;

#define HOOK_PROPERTY_NODE_ID  "nodeId"
#define HOOK_PROPERTY_HOOK_NAME "hookName"

namespace PatternCapture {

    struct HookCallDetails : public StringSerializable {
        string nodeId;
        string hookName;
        map<string, string> data;
        TO_JSON_STRING(HookCallDetails, nodeId, data, hookName);
    };

    class HookServer {
        private:
            vector<Hook *> hooks;
            int port;
            Scheduler &scheduler;
        public:
            HookServer(int port, Scheduler &scheduler);
            void addHook(Hook *);
            void start();
            void generateToken();
    };
};

#endif

