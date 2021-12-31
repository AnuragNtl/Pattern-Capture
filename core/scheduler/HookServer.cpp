#include <thread>
#include "HookServer.h"
#include "./cpp-httplib/httplib.h"
#include "../../StringSerializable.h"

using namespace httplib;
using namespace PatternCapture;

namespace PatternCapture {

    HookServer :: HookServer(int port, Scheduler &scheduler) : port(port), scheduler(scheduler) { }

    void HookServer :: addHook(Hook *hook) {
        hooks.push_back(hook);
    }

    void HookServer :: start() {
        new thread([this] () {
                Server server;
                server.Post("/hookUpdate", [this] (const Request &request, Response &response) {
                        HookCallDetails details = loadJson<HookCallDetails>(request.body);
                        map<string, string> data = details.data;
                        HookProperties hookProperties;
                        for(const auto &it : data) {
                        hookProperties[it.first] = it.second;
                        }
                        hookProperties[HOOK_PROPERTY_NODE_ID] = details.nodeId;
                        hookProperties[HOOK_PROPERTY_HOOK_NAME] = details.hookName;
                        scheduler.executeOnCallHook(hookProperties);
                        });
                server.listen("127.0.0.1", this->port);
        });

    }

    

};

