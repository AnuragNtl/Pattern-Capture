#include "./ProcessCapture.h"
#include <fstream>
#include "../../CommonUtils.h"

using namespace PatternCapture;

ProcessDetails ProcessCapture :: capture(map<string, string> params) {
    string pid = params["pid"];
    string basePath = "/proc/" + pid + "/";
    std::ifstream in(basePath + "cmdline");
    ProcessDetails processDetails;
    processDetails.cmdline = getContents(std::move(in));
    processDetails.pid = pid;
    processDetails.cwd = readLink(basePath + "/cwd");
    processDetails.processName = readLink(basePath + "/exe");
    return processDetails;
}

vector<string> getDependencyTypes() {
    return {"capture"};
}

Dependency* getDependency(const char *dependencyName) {
    return new ProcessCapture;
}

string ProcessCapture :: getId() const {
    return "processCapture";
}




