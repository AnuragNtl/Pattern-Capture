#ifndef SCHEDULER_H
#define SCHEDULER_H
/* 
 *
 *The dependencies are loaded
 Input graph is read and parsed:
  passed to appropriate engine
  converted to appropriate format
 Read by engine
  Engine executes all dependencies
  Engine is modulized with pluggable modules, such as logging and current status module
    Hooks can be inserted in engine

    Examples of engines:
    JNI Engine
    Python Engine
    Groovy Engine
    Native Engine : Default

    So, its specified in input graph,  to execute dependency D with engine E, along with input params, and to pass output to the next dependency.

 * */

#include "../engine/graphparser/GraphParser.h"
#include <vector>
#include <core/engine/hooks/Hooks.h>
#include <thread>
#include <future>

using namespace PatternCapture;
using namespace std;


namespace PatternCapture {
    class Scheduler {

        private:
            void initializeHooks(const Graph &graph, vector<Hook*> &, vector<Hook*> &);
            void validateGraph(const Graph &);
            void validateAndAssignDependencies(const Graph &); 
            void validateAndAssignAllDependencies(Node *node);
            void executeNodes(const Graph &, const vector<Hook*> &, const vector<Hook*> &, const set<Node*> :: iterator &, const set<Node*> :: iterator&, void *inputData = NULL);
            static void executeSingleNode(const Graph &&, const vector<Hook*> &&, const vector<Hook*> &&, Node &&, Scheduler *scheduler, void *inputData = NULL);
        public:
            Scheduler();
            void execute(const Graph &);
    };
};

#endif

