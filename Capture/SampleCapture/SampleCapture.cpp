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

int SampleCapture :: capture(map<string, string> input) {
    //this_thread::sleep_for(chrono::seconds(20));
  cout << "::\n";
  for(auto &i1 : input) {
      cout << i1.first << " " << i1.second <<"\n";
  }
  int *p = new int;
  *p = 2;
  return *p;
}



