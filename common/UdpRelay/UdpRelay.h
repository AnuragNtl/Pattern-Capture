#ifndef UDP_RELAY_HOOK_H

#define UDP_RELAY_HOOK_H

#include "../Common.h"
#include "../../CommonUtils.h"
#include "../../core/engine/hooks/Hooks.h"

#define UDP_RELAY_HOST "udpRelayHost"
#define UDP_RELAY_PORT "udpRelayPort"
#define MESSAGE "message"
#define MESSAGE_LENGTH "messageLength"

class UdpRelayHook : public Hook {
    public:
        void executeHook(const HookData &);
        std::string getId() const;
        std::set<std::string> getRequiredParameters();
        HookType getHookType();
};

class UdpRelay : public PatternCapture::CommonDependency<PatternCapture::BinData, bool> {
    public:
        bool getOutput(PatternCapture::BinData input, map<string, string>) const;
        std::string getId() const;
};

extern bool relayUdp(string host, string post, PatternCapture::BinData message);

extern "C" {
    extern std::vector<std::string> getDependencyTypes();
    extern Dependency* getDependency(const char *dependencyName);
}



#endif

