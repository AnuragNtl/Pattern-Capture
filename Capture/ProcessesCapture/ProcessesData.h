#ifndef PROCESSES_DATA

#define PROCESSES_DATA

#include <time.h>
#include <vector>

#include "../../StringSerializable.h"

using namespace PatternCapture;

    struct ProcessData : public StringSerializable {
        string user, pid, tty;
        time_t time, start;
        string command;
        TO_JSON_STRING(ProcessData, user, pid, tty, time, start, command);
    };

    struct ProcessesData : public StringSerializable {
        vector<ProcessData> processesData;
        TO_JSON_STRING(ProcessesData, processesData);
    };

#endif

