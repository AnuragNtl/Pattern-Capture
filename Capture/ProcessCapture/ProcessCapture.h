#ifndef PROCESS_CAPTURE_H

#define PROCESS_CAPTURE_H

#include "../../StringSerializable.h"
#include "../CaptureSource.h"
#include "../../nlohmann/json.hpp"

using namespace std;
using namespace PatternCapture;

namespace PatternCapture {

    struct ProcessDetails : public StringSerializable {
        string processName,
               pid,
               tty,
               start, time, cmdline, cwd;
        string environment;
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(ProcessDetails, processName, pid, tty, start, time, cmdline, cwd, environment)
        operator string() const;
    };

    class ProcessCapture : public CaptureSource<ProcessDetails> {
        public:
            ProcessDetails capture(map<string, string>);
            string getId() const;
    };
};

extern "C" {
    extern vector<string> getDependencyTypes();
    extern Dependency* getDependency(const char *dependencyName);
}

#endif


