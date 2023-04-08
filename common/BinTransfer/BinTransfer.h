#ifndef BIN_CAPTURE_H

#define BIN_CAPTURE_H

#define COMMAND_OPTION "command"

#include <string>
#include <vector>
#include "../Common.h"
#include "../../StringSerializable.h"
#include "../../CommonUtils.h"

    // bin -> string
    // string -> bin
    // bin -> bin 
    // string -> string

    class BinTransfer : public CommonDependency<PatternCapture::BinData, PatternCapture::BinData> {
        PatternCapture::BinData getOutput(PatternCapture::BinData, std::map<std::string, std::string>) const;
        string getId() const;
    };

extern "C" {
    extern std::vector<std::string> getDependencyTypes();
    extern Dependency* getDependency(const char *dependencyName);
}

#endif

