#ifndef COMMAND_LINE_H

#define COMMAND_LINE_H

#include <vector>
#include "../Common.h"
#include "../../Dependencies.h"

namespace PatternCapture {
    class CommandLine : public CommonDependency<string, string> {
        public:
            string getOutput(string input, map<string, string>) const;
            string getId() const;
    };
};

extern "C" {
    extern vector<string> getDependencyTypes();
    extern PatternCapture::Dependency* getDependency(const char *dependencyName);
}


#endif

