#include <fstream>
#include "./ProcessCapture.h"
#include "../../CommonUtils.h"

using namespace PatternCapture;
using nlohmann::json;

ProcessDetails :: operator string() const {
    json data;
    to_json(data, *this);
    cout << data.dump() << "\n";
    return data.dump();
}

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




