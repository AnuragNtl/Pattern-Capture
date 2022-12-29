#ifndef BIN_CAPTURE_H

#define BIN_CAPTURE_H

#define COMMAND_OPTION "command"

#include <string>
#include <vector>
#include "../Common.h"
#include "../../StringSerializable.h"

    // bin -> string
    // string -> bin
    // bin -> bin 
    // string -> string
    struct BinData : public StringSerializable {
        private:
            void assign(std::string);
        public:
        char *data;
        int length;
        BinData& operator=(std::string);
        BinData();
        BinData(std::string);
        operator std::string();
    };

    class BinTransfer : public CommonDependency<BinData, BinData> {
        BinData getOutput(BinData, std::map<std::string, std::string>) const;
        string getId() const;
    };

extern "C" {
    extern std::vector<std::string> getDependencyTypes();
    extern Dependency* getDependency(const char *dependencyName);
}

#endif

