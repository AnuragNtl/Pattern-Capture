#include <vector>
#include "ProcessesCapture.h"
#include "../../CommonUtils.h"

using namespace std;

ProcessesData ProcessesCapture :: capture(map<string, string> input) {
    vector<string> files = listDirectory("/proc");
    for(const auto &file : files) {
        
        int val = std::stoi(file);
    }

}

vector<string> getDependencyTypes() {
    return {"capture"};
}

Dependency* getDependency(const char *dependencyName) {
    return new ProcessesCapture;
}


