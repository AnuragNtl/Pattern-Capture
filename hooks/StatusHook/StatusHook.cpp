#include "StatusHook.h"
#include <iostream>
#include <chrono>

using namespace PatternCapture;
using namespace std;


string StatusHook :: getId() const {

    return "statusHook";
}

StatusHook :: StatusHook() {

    thread *statusThread = new thread(printStatus, this);
    statusThread->detach();
}


void StatusHook :: printStatus(StatusHook *statusHook) {

    while(1) {
        this_thread::sleep_for(chrono::seconds(2));
        statusHook->statusMutex.lock();
        cout << "---------------------------------Currently Executing Dependencies ------------\n";

        for(auto &dependencyId : statusHook->currentlyExecutingDependencies) {
            cout <<  dependencyId << "\n";
        }
        statusHook->statusMutex.unlock();
    }
}

void StatusHook :: executeHook(const HookData &hookData) {


    statusMutex.lock();
    currentlyExecutingDependencies.insert(hookData.node.id);
    statusMutex.unlock();
}

HookType StatusHook :: getHookType() {
    return EXECUTE_BEFORE;
}

Dependency* getDependency(const char *dependencyName) {

  return new StatusHook;
}

vector<string> getDependencyTypes() {
  vector<string> dependencyType = {DEPENDENCY_TYPE_HOOKS};
  return dependencyType;
}


