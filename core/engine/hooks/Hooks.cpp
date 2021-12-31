#include "Hooks.h"
#include "../../../Dependencies.h"

using namespace PatternCapture;

HookData :: HookData(const Node &node, const HookProperties &) : node(node), hookProperties(hookProperties) { }

void* Hook :: operator()(void *input) {

   HookData *hookData = (HookData *)(input);
   executeHook(*hookData);
   return nullptr;
}

void* Hook :: operator()(void *input, map<string, string> params) {
    HookData *hookData = reinterpret_cast<HookData*>(input);
    executeHook(*hookData);
    return NULL;
}


