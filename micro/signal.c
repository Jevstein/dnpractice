#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include <sys/time.h>

// log
#define LOG_ERR(fmt,...) { time_t now = time(NULL); printf("[%.24s][error][srv] "fmt" ["__FILE__":%s().%d]\n", ctime(&now), ##__VA_ARGS__, __FUNCTION__, __LINE__); }
#define LOG_EXP(fmt,...) { time_t now = time(NULL); printf("[%.24s][exception][srv] "fmt" ["__FILE__":%s().%d]\n", ctime(&now), ##__VA_ARGS__, __FUNCTION__, __LINE__); }
#define LOG_WAR(fmt,...) { time_t now = time(NULL); printf("[%.24s][warning][srv] "fmt"\n", ctime(&now), ##__VA_ARGS__); }
#define LOG_INF(fmt,...) { time_t now = time(NULL); printf("[%.24s][inf][srv] "fmt"\n", ctime(&now), ##__VA_ARGS__); }
#define LOG_DBG(fmt,...) { time_t now = time(NULL); printf("[%.24s][dbg][srv] "fmt"\n", ctime(&now), ##__VA_ARGS__); }


void sig_routine(int signo) {
    switch (signo) {
        case SIGALRM:
            LOG_INF("Catch a signal -- SIGALRM");
        break;
        case SIGVTALRM:
            LOG_INF("Catch a signal -- SIGVTALRM");
        break;
    }
    return;
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