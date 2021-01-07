#include "Hooks.h"
#include "../../../Dependencies.h"

using namespace PatternCapture;


void* Hook :: operator()(void *input) {

   Node *node = (Node *)(input);
   executeHook(*node);
   return nullptr;
}

void* Hook :: operator()(void *input, map<string, string> params) {
    Node *node = reinterpret_cast<Node*>(input);
    executeHook(*node, params);
    return NULL;
}


