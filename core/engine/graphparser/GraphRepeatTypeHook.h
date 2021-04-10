#ifndef GRAPH_REPEAT_TYPE_HOOK

#define GRAPH_REPEAT_TYPE_HOOK

#include "GraphParser"

#define ONCE_VALUE "ONCE"
#define CONTINUOUS_VALUE "CONTINUOUS"
#define NODE_REPEAT_KEY "repeat"
#define SCHEDULED_VALUE "SCHEDULED"
#define REPEAT_TIMES_KEY "repeatTimes"

namespace PatternCapture {

    class GraphRepeatTypeHook : public GraphPropertyHook {

        private:
            GraphRepeatTypeHook();
            static map<string, NodeRepeat> nodeRepeatTypeMap;
            initializeNodeRepeatTypeMap();
        protected:
            void initializeNodeRepeatTypeMap();
        public:
            virtual void operator()(Graph &graph, const map<string, string> &properties) const;
    };

    GraphRepeatTypeHook :: GraphRepeatTypeHook() {
        initializeNodeRepeatTypeMap();
    }

    void GraphRepeatTypeHook :: operator()(Graph &graph, map<string, string> &properties) const {

        if(properties.find(NODE_REPEAT_KEY) != properties.end() && nodeRepeatTypeMap.find(properties[NODE_REPEAT_KEY]) != nodeRepeatTypeMap.end()) {
            graph.repeatType = nodeRepeatTypeMap[properties[NODE_REPEAT_KEY]];
        } else if(properties.find(REPEAT_TIMES_KEY) != properties.end()) {
            graph.repeatTimes = stoi(properties[REPEAT_TIMES_KEY]);
        }
    }
    
    void GraphRepeatTypeHook :: initializeNodeRepeatTypeMap() {
        if(nodeRepeatTypeMap.empty()) {

            nodeRepeatTypeMap[ONCE_VALUE] = NodeRepeat::ONCE;
            nodeRepeatTypeMap[CONTINUOUS_VALUE] = NodeRepeat::CONTINUOUS;
            nodeRepeatTypeMap[SCHEDULED_VALUE] = NodeRepeat::SCHEDULED;
        }
    }
    map<string, NodeRepeat> GraphRepeatTypeHook :: nodeRepeatTypeMap = map<string, NodeRepeat>();
};

#endif

