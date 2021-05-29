#include "CronScheduler.h"
#include "ccronexpr/ccronexpr.h"
#include <ctime>
#include <unistd.h>
#include <cstring>



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
        do {
            time_t scheduledTime = cron_next(&expr, cronNext);
            struct tm *timeDetails = localtime(&cronNext);
            strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", timeDetails);
            cout << buffer << "\n";
            double timeDiff = difftime(cronNext, scheduledTime);
            //usleep(timeDiff * 1);
            cronNext = scheduledTime;
        } while(true);
    }

};


