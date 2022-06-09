#ifndef SCHEDULER_FACTORY_H

#define SCHEDULER_FACTORY_H

#include <map>
#include "../engine/graphparser/GraphParser.h"
#include <functional>

using namespace std;

namespace PatternCapture {
    class GraphScheduler {
        public:
            virtual void operator()(const Graph &graph, std::function<void()> ) = 0;
    };

    class SchedulerFactory {

        private:
            static map<NodeRepeat, GraphScheduler*> NODE_REPEAT_MAP;
            void initializeNodeRepeatMap();
        public:
            GraphScheduler* getScheduler(const NodeRepeat &nodeRepeat) const;
            SchedulerFactory();
            static vector<string> getSupportedValues();
    };

};


#endif

