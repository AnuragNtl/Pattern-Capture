#include "CronScheduler.h"
#include "ccronexpr/ccronexpr.h"
#include <ctime>
#include <unistd.h>
#include <cstring>
#include <cmath>
#include <thread>

#define MICROSECONDS 1000000

using namespace std;

namespace PatternCapture {

    void CronScheduler :: operator()(const Graph &graph, std::function<void()> onSchedule) {
        cron_expr expr;
        const char *err = NULL;
        memset(&expr, 0, sizeof(expr));
        cron_parse_expr(graph.schedule.c_str(), &expr, &err);
        if(err) {
            throw std::exception();
        }
        time_t currentTime = time(NULL);
        time_t cronNext = currentTime;
        char buffer[80];
        thread *scheduleThread = NULL;
        do {
            time_t scheduledTime = cron_next(&expr, cronNext);
            struct tm *timeDetails = localtime(&cronNext);
            strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", timeDetails);
            cout << buffer << "\n";
            double timeDiff = abs(difftime(scheduledTime, cronNext));
            cout << "timediff = " << timeDiff <<"\n";
            usleep(timeDiff * MICROSECONDS);
            if(scheduleThread != NULL) {
                scheduleThread->join();
                delete scheduleThread;
            }
            scheduleThread = new thread(onSchedule);
            cronNext = time(NULL);
        } while(true);
    }

};


