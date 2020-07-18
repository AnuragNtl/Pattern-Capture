#include "Hooks.h"
#include "../../../Dependencies.h"

using namespace PatternCapture;


void* Hook :: operator()(void *input) {

   Node *node = (Node *)(input);
   executeHook(*node);
   return nullptr;
}

