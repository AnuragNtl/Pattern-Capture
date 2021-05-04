#include "ContinuousScheduler.h"

namespace PatternCapture {

    void ContinuousScheduler :: operator()(const Graph &graph, std::function<void()> onSchedule) {
        for(int i = 0; i < graph.repeatTimes; i++) {
            onSchedule();
        }
    }
};

