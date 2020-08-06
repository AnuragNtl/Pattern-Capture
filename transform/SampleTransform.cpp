#include "SampleTransform.h"
#include <iostream>

using namespace std;

string SampleTransform :: getId() const {
    return "sampleTransform";
}

int SampleTransform :: transform(int input, map<string, string>) {
    int i1 = input * 2;
    cout << i1 << "\n";
    return i1;
}

Dependency* getDependency(const char *) {
    return new  SampleTransform;
}

vector<string> getDependencyTypes() {
    return {"sampleTransform"};
}














