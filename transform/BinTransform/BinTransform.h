#ifndef BIN_TRANSFORM_H
#define BIN_TRANSFORM_H

#include "../Transform.h"
#include "../../CommonUtils.h"

class ToBinTransform : public PatternCapture::Transform<std::string, PatternCapture::BinData> {
    public:
        PatternCapture::BinData transform(std::string, std::map<std::string, std::string>) const;
        std::string getId() const;
};

class BinToAsciiTransform : public PatternCapture::Transform<PatternCapture::BinData, std::string> {
    public:
        std::string transform(PatternCapture::BinData, std::map<std::string, std::string>) const;
        std::string getId() const;
};

extern "C" {
    extern std::vector<string> getDependencyTypes();
    extern PatternCapture::Dependency* getDependency(const char *dependencyName);
}


#endif

