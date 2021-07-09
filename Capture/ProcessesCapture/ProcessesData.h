#ifndef PROCESSES_DATA

#define PROCESSES_DATA

#include <time.h>

namespace PatternCapture {

    struct ProcessesData : public StringSerializable {
        string user, pid, tty;
        time_t time, start;
        string command;
        TO_JSON_STRING(user, pid, tty, time, start, command);
    };
};

#endif

