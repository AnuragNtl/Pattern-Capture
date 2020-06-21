#include "Scheduler.h"
#include <Dependencies.h>
#include <vector>
#include <algorithm>
#include <thread>
#include <future>

using namespace std;

using namespace PatternCapture;


Scheduler :: Scheduler() {

}

void Scheduler :: execute(const Graph &graph) {

    vector<Hook*> executeBefore;
    vector<Hook*> executeAfter;
    initializeHooks(graph, executeBefore, executeAfter);
    validateGraph(graph);
    executeNodes(graph, executeBefore, executeAfter, graph.rootNodes.begin(), graph.rootNodes.end());
}

void Scheduler :: initializeHooks(const Graph &graph, vector<Hook*> &executeBefore, vector<Hook*> &executeAfter) {
    for(string hookId : graph.hooks) {
        Hook *hook = dynamic_cast<Hook*>(getDependency(DEPENDENCY_TYPE_HOOKS, hookId));
        if(hook == NULL) {
            throw DependencyException(hookId + " is not a hook");
        }
        switch(hook->getHookType()) {
            case (HookType::EXECUTE_BEFORE): executeBefore.push_back(hook);
                                           break;
            case (HookType::EXECUTE_AFTER): executeAfter.push_back(hook);
                                          break;
            default:
            throw DependencyException("Invalid hookType for hook " + hookId);
                                          break;

        }
    }
}

void Scheduler :: validateAndAssignDependencies(const Graph &graph) {

    for_each(graph.rootNodes.begin(), graph.rootNodes.end(), [this] (Node *node) {
            
            validateAndAssignAllDependencies(node);
            }); 
}

void Scheduler :: validateAndAssignAllDependencies(Node *node) {

    if(!dependencyExists(DependencyKey(node->type, node->id))) {
        throw DependencyException("Invalid dependency " + node->id);
    }

    node->dependency = getDependency(node->type, node->id);
    for_each(node->deliversToNodes.begin(), node->deliversToNodes.end(), [this] (Node *subnode) {

            validateAndAssignAllDependencies(subnode);
            });
}

void Scheduler :: validateGraph(const Graph &graph) {

    validateAndAssignDependencies(graph);
}


void Scheduler :: executeSingleNode(const Graph &graph, const vector<Hook*> &executeBefore, const vector<Hook*> &executeAfter, Node &node,  Scheduler *scheduler, void *inputData) {

    Dependency &dependency = *(node.dependency);
    void *dependencyResponse;

    for(auto beforeHook : executeBefore)
        (*beforeHook)(NULL);

    if(inputData == NULL) {
        dependencyResponse = dependency(&node.inputParams);
    } else {
        dependencyResponse = dependency(inputData);
    }

    for(auto afterHook : executeAfter)
        (*afterHook)(NULL);
    
    scheduler->executeNodes(graph, executeBefore, executeAfter, node.deliversToNodes.begin(), node.deliversToNodes.end(), dependencyResponse);

}

void Scheduler :: executeNodes(const Graph &graph, const vector<Hook*> &executeBefore, const vector<Hook*> &executeAfter, const set<Node*> :: iterator &firstNode, const set<Node*> :: iterator &lastNode, void *inputData) {

    vector<thread> nodeThreads;
    for_each(firstNode, lastNode, [graph, executeBefore, executeAfter, firstNode, lastNode, inputData, &nodeThreads] (Node *node) {
            thread nodeThread(executeSingleNode ,graph, executeBefore, executeAfter, firstNode, lastNode);
            nodeThreads.push_back(nodeThread);
    });

    for_each(nodeThreads.begin(), nodeThreads.end(), [] (thread nodeThread) {

            nodeThread.join();
            });
}

