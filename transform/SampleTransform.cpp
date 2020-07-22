#include "SampleTransform.h"
#include <iostream>

using namespace std;

string SampleTransform :: getId() const {
    return "sampleTransform";
}

void* SampleTransform :: operator()(void *input) {
    cout << "In sampleTransform\n";
    int *i = (int *) input;
    int *i1 = new int;
    *i1 = (*i) * 2;
    cout << *i1 << "\n";
    return i1;
}

Dependency* getDependency(const char *) {
    return new  SampleTransform;
}

vector<string> getDependencyTypes() {
    return {"sampleTransform"};
}



