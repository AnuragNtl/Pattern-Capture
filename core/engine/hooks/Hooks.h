#ifndef HOOKS_H

#define HOOKS_H

#include "../graphparser/GraphParser.h"
#include <Dependencies.h>

using namespace PatternCapture;

namespace PatternCapture {
    
    enum HookType { EXECUTE_BEFORE, EXECUTE_AFTER };
   class Hook : public Dependency {
        public:
            virtual HookType getHookType() = 0;
    };

};


#endif

