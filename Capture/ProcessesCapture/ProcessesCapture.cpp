#include <vector>
#include <fstream>
#include "ProcessesCapture.h"
#include "ProcessesData.h"
#include "../../CommonUtils.h"

using namespace std;
using namespace PatternCapture;

ProcessesData ProcessesCapture :: capture(map<string, string> input) {
    vector<string> files = listDirectory("/proc");
    ProcessesData processesData;
    for(const auto &file : files) {
        
        string cmdlineFile = "/proc/" + file + "/cmdline";
        if(!isNumeric(file) || 
                !pathExists(cmdlineFile)) {
            continue;
        }
        ProcessData processData;
        processData.pid = file;
        cout << "pid = " << processData.pid << "\n";
        processData.command = getContents(std::ifstream(cmdlineFile, ios::in | ios::binary));
        cout << "cmdline = " << processData.command << "\n";
        processesData.processesData.push_back(processData);
    }
    return processesData;

}

string ProcessesCapture :: getId() const {
    return "processesCapture";
}

vector<string> getDependencyTypes() {
    return {"capture"};
}

Dependency* getDependency(const char *dependencyName) {
    return new ProcessesCapture;
}


