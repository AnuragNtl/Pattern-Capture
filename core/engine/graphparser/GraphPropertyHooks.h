#ifndef GRAPH_PROPERTY_HOOKS_H

#define GRAPH_PROPERTY_HOOKS_H

#include "GraphParser.h"
#include "GraphRepeatTypeHook.h"

namespace PatternCapture {

    const vector<GraphPropertyHook*> GRAPH_PROPERTY_HOOKS = 
    {
        dynamic_cast<GraphPropertyHook*>(new GraphRepeatTypeHook())
    };
};

#endif

