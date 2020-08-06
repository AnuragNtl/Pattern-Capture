#ifndef SAMPLE_TRANSFORM_H
#define SAMPLE_TRANSFORM

#include "Transform.h"

using namespace PatternCapture;

class SampleTransform : public Transform<int, int> {

    public:
        string getId() const;
        int transform(int input, map<string, string> params);

};

extern "C" {

        extern Dependency* getDependency(const char *);

        extern vector<string> getDependencyTypes();

}
#endif

