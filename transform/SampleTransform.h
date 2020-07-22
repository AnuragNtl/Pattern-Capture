#ifndef SAMPLE_TRANSFORM_H
#define SAMPLE_TRANSFORM

#include "../Dependencies.h"

using namespace PatternCapture;

class SampleTransform : public Dependency {

    public:
        string getId() const;
        void* operator()(void *);

};

extern "C" {

        extern Dependency* getDependency(const char *);

        extern vector<string> getDependencyTypes();

}
#endif

