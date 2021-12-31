#ifndef STATUS_HOOK_H
#define STATUS_HOOK_H

#include "../../core/engine/hooks/Hooks.h"
#include <thread>
#include <mutex>


class StatusHook : public Hook {
    private:
        mutex statusMutex;
        set<string> currentlyExecutingDependencies;
    public:
        StatusHook();
        HookType getHookType();
        string getId() const;
        void executeHook(const HookData &); 
        static void printStatus(StatusHook *);
};


extern "C" {
    extern vector<string> getDependencyTypes();
    extern Dependency* getDependency(const char *dependencyName);
}
#endif


