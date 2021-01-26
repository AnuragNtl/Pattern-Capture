#include "./ProcessCapture.h"
#include <fstream>
#include "../../CommonUtils.h"

using namespace PatternCapture;

ProcessDetails ProcessCapture :: capture(map<string, string> params) const {
    string pid = params["pid"];
    string basePath = "/proc/" + pid + "/";
    std::ifstream in(basePath + "cmdline");
    ProcessDetails processDetails;
    processDetails.cmdline = getContents(std::move(in));
    processDetails.pid = pid;
    processDetails.cwd = readLink(basePath + "/cwd");
}




