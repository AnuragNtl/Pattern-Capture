#include "SchedulerFactory.h"
#include "ContinuousScheduler.h"
#include "OnceScheduler.h"
#include "CronScheduler.h"



namespace PatternCapture {

    GraphScheduler* SchedulerFactory :: getScheduler(const NodeRepeat &nodeRepeat) const {
        if(NODE_REPEAT_MAP.find(nodeRepeat) != NODE_REPEAT_MAP.end()) {
            return NODE_REPEAT_MAP[nodeRepeat];
        } else {
            throw std::exception();
        }
    }

    SchedulerFactory :: SchedulerFactory() {
        initializeNodeRepeatMap();
    }

    void SchedulerFactory :: initializeNodeRepeatMap() {

        if(NODE_REPEAT_MAP.size() > 0) {

            return;
        }

        NODE_REPEAT_MAP[CONTINUOUS] = new ContinuousScheduler;
        NODE_REPEAT_MAP[ONCE] = new OnceScheduler;
        NODE_REPEAT_MAP[SCHEDULED] = new CronScheduler;
    }

    map<NodeRepeat, GraphScheduler*> SchedulerFactory :: NODE_REPEAT_MAP = map<NodeRepeat, GraphScheduler*>();

    vector<string> SchedulerFactory :: getSupportedValues() {
        return {CONTINUOUS_VALUE, SCHEDULED_VALUE, ONCE_VALUE };
    }
};



