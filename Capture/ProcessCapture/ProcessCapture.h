#ifndef PROCESS_CAPTURE_H

#define PROCESS_CAPTURE_H

#include "../../StringSerializable.h"
#include "../CaptureSource.h"

using namespace std;
using namespace PatternCapture;

namespace PatternCapture {

    struct ProcessDetails : public StringSerializable {
        string processName,
               pid,
               tty,
               start, time, cmdline, cwd;
        string environment;
        TO_JSON_STRING(ProcessDetails, processName, pid, tty, start, time, cmdline, cwd, environment)
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


