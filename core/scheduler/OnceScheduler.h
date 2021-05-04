#ifndef ONCE_SCHEDULER_H

#define ONCE_SCHEDULER_H

#include "SchedulerFactory.h"

namespace PatternCapture {
    class OnceScheduler : public GraphScheduler {
        public:
            void operator()(const Graph&, std::function<void()>);
    };
};

#endif

