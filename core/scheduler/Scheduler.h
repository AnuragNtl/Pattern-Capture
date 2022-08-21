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


#include <vector>
using namespace std;

#include <core/engine/hooks/Hooks.h>
#include "../engine/graphparser/GraphParser.h"
#include <thread>
#include <future>
#include <mutex>
#include "./core/engine/graphparser/schema/SchemaProperties.h"

using namespace PatternCapture;


namespace PatternCapture {
    class Scheduler {

        private:
            void executeOnCallHook(Hook *hook);
            void initializeHooks(const Graph &graph, vector<Hook*> &, vector<Hook*> &, vector<Hook*> &executeOnCall);
            void validateGraph(const Graph &);
            void validateAndAssignDependencies(const Graph &); 
            void validateAndAssignAllDependencies(Node *node);
            void executeNodes(const Graph &, const vector<Hook*> &, const vector<Hook*> &, const set<Node*> :: iterator &, const set<Node*> :: iterator&, void *inputData = NULL);
            static void executeSingleNode(const Graph &, const vector<Hook*> &&, const vector<Hook*> &&, Node &, Scheduler *scheduler, void *inputData = NULL);
            vector<Hook*> executeOnCall;
            const Graph &graph;
            mutex callbackHookMutex;
        public:
            Scheduler(const Graph &);
            void execute();
            void executeOnCallHook(HookProperties &hookProperties);
    };
    extern AnyOfProperties generateSchemaProperties();
};

#endif

