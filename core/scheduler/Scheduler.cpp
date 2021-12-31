#include "Scheduler.h"
#include "Dependencies.h"
#include <vector>
#include <algorithm>
#include <thread>
#include <future>
#include <iostream>
#include "SchedulerFactory.h"
#include "HookServer.h"

using namespace std;

using namespace PatternCapture;


Scheduler :: Scheduler(const Graph &graph) : graph(graph) {

}

void Scheduler :: execute() {

    vector<Hook*> executeBefore;
    vector<Hook*> executeAfter;
    vector<Hook*> executeOnCall;
    cout << graph << "\n";
    initializeHooks(graph, executeBefore, executeAfter, executeOnCall);
    this->executeOnCall = executeOnCall;
    validateGraph(graph);
    SchedulerFactory schedulerFactory;
    HookServer hookServer(8089, *this);
    hookServer.start();
    GraphScheduler *graphScheduler = schedulerFactory.getScheduler(graph.repeatType);
    (*graphScheduler)(graph, [this, &executeBefore, &executeAfter] () {
            executeNodes(graph, executeBefore, executeAfter, graph.rootNodes.begin(), graph.rootNodes.end());
            });
    /*switch(graph.repeatType) {
        case ONCE:
            executeNodes(graph, executeBefore, executeAfter, graph.rootNodes.begin(), graph.rootNodes.end());
            break;
        case CONTINUOUS:
            for(int i = 0; i < graph.repeatTimes; i++) {
                executeNodes(graph, executeBefore, executeAfter, graph.rootNodes.begin(), graph.rootNodes.end());
            }
            break;
        default: break;
    }*/
}

void Scheduler :: initializeHooks(const Graph &graph, vector<Hook*> &executeBefore, vector<Hook*> &executeAfter, vector<Hook*> &executeOnCall) {
    for(auto hookProperties : graph.hookProperties) {
        string hookId = hookProperties.first;
        Hook *hook = dynamic_cast<Hook*>(getDependency(DEPENDENCY_TYPE_HOOKS, hookId));
        if(hook == NULL) {
            throw DependencyException(hookId + " is not a hook");
        }
        switch(hook->getHookType()) {
            case (HookType::EXECUTE_BEFORE): executeBefore.push_back(hook);
                                           break; case (HookType::EXECUTE_AFTER): executeAfter.push_back(hook); break; 
            case (HookType::EXECUTE_ON_CALL): executeOnCall.push_back(hook);
                                              break;
            default: throw DependencyException("Invalid hookType for hook " + hookId);
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

    if(!dependencyExists(DependencyKey(node->type, node->dependencyId))) {
        throw DependencyException("Invalid dependency " + node->dependencyId);
    }

    node->dependency = getDependency(node->type, node->dependencyId);
    for_each(node->deliversToNodes.begin(), node->deliversToNodes.end(), [this] (Node *subnode) {

            validateAndAssignAllDependencies(subnode);
            });
}

void Scheduler :: validateGraph(const Graph &graph) {

    validateAndAssignDependencies(graph);
}


void Scheduler :: executeSingleNode(const Graph &graph, const vector<Hook*> &&executeBefore, const vector<Hook*> &&executeAfter, Node &node,  Scheduler *scheduler, void *inputData) {

    Dependency &dependency = *(node.dependency);
    void *dependencyResponse;

    for(auto beforeHook : executeBefore) {
        HookData *hookData = new HookData(node, graph.hookProperties.find(beforeHook->getId())->second);
        (*beforeHook)(hookData);
    }

    if(inputData == NULL) {
        dependencyResponse = dependency(&node.inputParams);
    } else {
        dependencyResponse = dependency(inputData, node.inputParams);
        //delete inputData;
    }

    for(auto afterHook : executeAfter) {
        HookData *hookData = new HookData(node, graph.hookProperties.find(afterHook->getId())->second);
        (*afterHook)(hookData);
    }
    
    scheduler->executeNodes(graph, executeBefore, executeAfter, node.deliversToNodes.begin(), node.deliversToNodes.end(), dependencyResponse);

}

void Scheduler :: executeNodes(const Graph &graph, const vector<Hook*> &executeBefore, const vector<Hook*> &executeAfter, const set<Node*> :: iterator &firstNode, const set<Node*> :: iterator &lastNode, void *inputData) {

    vector<thread*> nodeThreads;
    for_each(firstNode, lastNode, [this, &graph, &executeBefore, &executeAfter, &nodeThreads, inputData] (Node *node) {
            thread *nodeThread = new thread(executeSingleNode, std::ref(graph), executeBefore, executeAfter, std::ref(*node), this, inputData);
            nodeThreads.push_back(nodeThread);
    });

    for_each(nodeThreads.begin(), nodeThreads.end(), [] (thread *nodeThread) {

            nodeThread->join();
            });
}

void Scheduler :: executeOnCallHook(HookProperties &hookProperties) {
    callbackHookMutex.lock();
    cout << "Executing on call hook " << hookProperties << "\n";
    if((!hookProperties.hasProperty(HOOK_PROPERTY_NODE_ID))
            || (!hookProperties.hasProperty(HOOK_PROPERTY_HOOK_NAME))) {
        throw std::exception();
    }
    Node &node = graph.getNodeById(hookProperties[HOOK_PROPERTY_NODE_ID]);
    for(Hook *hook : executeOnCall) {
        HookData *hookData = new HookData(node, hookProperties);
        (*hook)(hookData);
    }
    callbackHookMutex.unlock();
}


