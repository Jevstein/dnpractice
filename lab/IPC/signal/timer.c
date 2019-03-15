#include "header.h"
#include <sys/time.h>

void sig_routine(int signo) {
    switch (signo) {
        case SIGALRM:
            LOG_INF("Catch a signal -- SIGALRM");
        break;
        case SIGVTALRM:
            LOG_INF("Catch a signal -- SIGVTALRM");
        break;
    }
}

int main()
{
    struct itimerval value, ovalue, value2;

    LOG_INF("process id is %d ", getpid());
    signal(SIGALRM, sig_routine);
    signal(SIGVTALRM, sig_routine);

    value.it_value.tv_sec = 2;
    value.it_value.tv_usec = 0;
    value.it_interval.tv_sec = 1;
    value.it_interval.tv_usec = 0;
    setitimer(ITIMER_REAL, &value, &ovalue);

    value2.it_value.tv_sec = 0;
    value2.it_value.tv_usec = 500000;
    value2.it_interval.tv_sec = 0;
    value2.it_interval.tv_usec = 500000;
    setitimer(ITIMER_VIRTUAL, &value2, &ovalue);

    // sleep (60);
    while(1);
}