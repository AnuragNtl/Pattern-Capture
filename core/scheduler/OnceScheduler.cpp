#include "OnceScheduler.h"

using namespace PatternCapture;
using namespace std;

namespace PatternCapture {

    void OnceScheduler :: operator()(const Graph &graph, function<void()> onSchedule) {
        onSchedule();
    }

};

