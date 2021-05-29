#ifndef CRON_SCHEDULER_H

#define CRON_SCHEDULER_H

#include "SchedulerFactory.h"

using namespace std;

namespace PatternCapture {

    class CronScheduler : public GraphScheduler {

        public:
            void operator()(const Graph &, std::function<void()>);
            

    };
};

#endif

