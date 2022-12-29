#include "../../CommonUtils.h"
#include "BinTransfer.h"


    void BinData :: assign(std::string details) {
        const char *content = details.c_str();
        this->data = new char[details.size() + 1];
        this->length = details.size();
        memcpy(this->data, content, this->length * sizeof(char));
    }

    BinData :: BinData() { }

    BinData :: BinData(std::string details) {
        assign(details);
    }

    BinData& BinData :: operator=(std::string details) {
        assign(details);
        return *this;
    }

    BinData :: operator std::string() {
        data[this->length] = '\0';
        return std::string(data);
    }

    BinData BinTransfer :: getOutput(BinData captureData, std::map<std::string, std::string> input) const {
        std::string command = input[COMMAND_OPTION];
        CommandOutput *output = getCommandOutput(captureData.data, captureData.length, command);
        BinData outputData;
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




