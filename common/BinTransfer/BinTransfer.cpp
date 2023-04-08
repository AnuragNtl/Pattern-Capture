#include "BinTransfer.h"


    PatternCapture::BinData BinTransfer :: getOutput(PatternCapture::BinData captureData, std::map<std::string, std::string> input) const {
        std::string command = input[COMMAND_OPTION];
        CommandOutput *output = getCommandOutput(captureData.data, captureData.length, command);
        PatternCapture::BinData outputData;
        if (output->outputLen > 0) {
            outputData.data = output->output;
            outputData.length = output->outputLen;
        } else if (output->errorLen > 0) {
            outputData.data = output->error;
            outputData.length = output->errorLen;
        }
        return outputData;
    }

    string BinTransfer :: getId() const {
        return "binTransfer";
    }

std::vector<std::string> getDependencyTypes() {
    return {"captureAndTransform"};
}

Dependency* getDependency(const char *dependencyName) {
    return new BinTransfer;
}




