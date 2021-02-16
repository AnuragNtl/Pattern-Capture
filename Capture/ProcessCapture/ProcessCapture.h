#ifndef PROCESS_CAPTURE_H

#define PROCESS_CAPTURE_H

#include "../CaptureSource.h"

using namespace std;

namespace PatternCapture {

    struct ProcessDetails {
        string processName,
               pid,
               tty,
               start, time, cmdline, cwd;
        string environment;
    };

    class ProcessCapture : public CaptureSource<ProcessDetails> {
        public:
            ProcessDetails capture(map<string, string>) const;
            string getId() const;
    };
};

extern "C" {
    extern vector<string> getDependencyTypes();
    extern Dependency* getDependency(const char *dependencyName);
}

#endif


