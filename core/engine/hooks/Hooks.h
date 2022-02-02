#ifndef HOOKS_H

#define HOOKS_H

#include "../graphparser/GraphParser.h"
#include "Dependencies.h"
#include <string>
#include <map>


#define DEPENDENCY_TYPE_HOOKS "hooks"

using namespace PatternCapture;

namespace PatternCapture {
    
    enum HookType { EXECUTE_BEFORE, EXECUTE_AFTER, EXECUTE_ON_CALL };
    struct HookData {
        const Node &node;
        const HookProperties &hookProperties;
        string message;
        HookData(const Node &, const HookProperties &);
    };

   class Hook : public virtual Dependency {
        public: virtual HookType getHookType() = 0;
            virtual void executeHook(const HookData &) { }
            virtual void* operator()(void *);
            virtual void* operator()(void *, std::map<std::string, std::string>);
            virtual map<string, string> getSampleValues() { }
    };

};


#endif

