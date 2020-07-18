#include "SampleCapture.h"

#include <iostream>

#include <chrono>
#include <thread>

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

int& SampleCapture :: capture(map<string, string> input) {
    this_thread::sleep_for(chrono::seconds(20));
  cout << "::\n";
  int *p = new int;
  *p = 6;
  return *p;
}



