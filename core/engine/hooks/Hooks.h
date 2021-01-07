#ifndef HOOKS_H

#define HOOKS_H

#include "../graphparser/GraphParser.h"
#include <Dependencies.h>
#include <string>
#include <map>


#define DEPENDENCY_TYPE_HOOKS "hooks"

using namespace PatternCapture;

namespace PatternCapture {
    
    enum HookType { EXECUTE_BEFORE, EXECUTE_AFTER };
   class Hook : public virtual Dependency {
        public:
            virtual HookType getHookType() = 0;
            virtual void executeHook(const Node &) {};
            virtual void executeHook(const Node &, map<string, string>) {}
            virtual void* operator()(void *);
            virtual void* operator()(void *, std::map<std::string, std::string>);
    };

};


#endif

