#ifndef CONTINUOUS_SCHEDULER_H

#define CONTINUOUS_SCHEDULER_H

#include "SchedulerFactory.h"

namespace PatternCapture {

    class ContinuousScheduler : public GraphScheduler {

        public:
            void operator()(const Graph &graph, std::function<void()> onSchedule);
    };
};

#endif

