#include "SampleCapture.h"

#include <iostream>

using namespace std;

string SampleCapture :: getId() const {

  return "sample capture";
}


vector<string> getDependencyTypes() {
  vector<string> dependencyType = {"sampleCapture"};
  return dependencyType;
}

Dependency* getDependency(const char *dependencyName) {

  return new SampleCapture;
}

int& SampleCapture :: capture(char *input[]) {
  cout << "::\n";
  int *p = new int;
  *p = 6;
  return *p;
}



