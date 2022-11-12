#ifndef BIN_CAPTURE_H

#define BIN_CAPTURE_H

#define COMMAND_OPTION "command"

namespace PatternCapture {

    struct BinCaptureData {
        char *data;
        int length;
    };

    class BinCapture : public CaptureSource<BinCaptureData> {
        BinCaptureData capture(std::map<std::string, std::string> input);
    };
};

extern "C" {
    extern std::vector<std::string> getDependencyTypes();
    extern Dependency* getDependency(const char *dependencyName);
}

#endif

