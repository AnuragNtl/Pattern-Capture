#include "BinTransform.h"

PatternCapture::BinData ToBinTransform :: transform(std::string input, std::map<std::string, std::string> params) const {
    return PatternCapture::BinData(input);
}

std::string BinToAsciiTransform :: transform(PatternCapture::BinData input, std::map<std::string, std::string> params) const {
    return (std::string)input;
}

std::string ToBinTransform :: getId() const {
    return "toBin";
}

std::string BinToAsciiTransform :: getId() const {
    return "toAscii";
}

std::vector<std::string> getDependencyTypes() {
    return {"toBinTransform", "toAsciiTransform"};
}

PatternCapture::Dependency* getDependency(const char *dependencyName) {
    if (string(dependencyName) == "toBinTransform") {
        return new ToBinTransform;
    } else {
        return new BinToAsciiTransform;
    }
}



