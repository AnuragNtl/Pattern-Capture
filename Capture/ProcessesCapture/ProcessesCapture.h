#ifndef PROCESSES_CAPTURE_H

#define PROCESSES_CAPTURE_H


#include "../CaptureSource.h"
#include "ProcessesData.h"

using namespace PatternCapture;

class ProcessesCapture : public CaptureSource<ProcessesData> {
    ProcessesData capture(map<string, string> input);
    string getId() const ;
};

extern "C" {
    extern vector<string> getDependencyTypes();
    extern Dependency* getDependency(const char *dependencyName);
}

#endif

