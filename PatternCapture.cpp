#include "Dependencies.h"
#include <iostream>
#include "CommonUtils.h"

using namespace std;
using namespace PatternCapture;

int main(int argc, char *argv[]) {
  cout << "__\n";
  initialize();
  for_each(dependencyTypeWiseTable.begin(), dependencyTypeWiseTable.end(), [] (pair<DependencyKey, Dependency*> entry) {
      cout << entry.first << "=" << entry.second <<"\n";
      });
  Dependency *dependency = dependencyTypeWiseTable[DependencyKey("sampleCapture", "sample capture")];
  cout << dependency->getId() <<"\n";
  cout << *((int *)(*dependency)(NULL)) <<"\n";
  return 0;
}

