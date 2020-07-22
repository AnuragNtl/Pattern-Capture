
#ifndef SAMPLE_CAPTURE_H
#define SAMPLE_CAPTURE_H

#include <iostream>
#include "Dependencies.h"
#include "../CaptureSource.h"

using namespace PatternCapture;
using namespace std;

class SampleCapture : public CaptureSource<int> {

  public:
    string getId() const;
    int capture(map<string, string>);
};

extern "C" {
extern vector<string> getDependencyTypes();
extern Dependency* getDependency(const char *dependencyName);
}
#endif

