/**
 * alarm()用来设置信号SIGALRM在经过参数seconds指定的秒数后传送给目前的进程。
 * 如果参数seconds 为0，则之前设置的闹钟会被取消，并将剩下的时间返回。返回值
 * 返回之前闹钟的剩余秒数，如果之前未设闹钟则返回0。
 * 
 * 已被弃用，建议使用setitimer
*/

#include "header.h"

void handler()
{
    LOG_INF("hello/n");
}

int main()
{
    int i;
    signal(SIGALRM, handler);
    alarm(5);

    for(i=1; i<7; i++) {
        LOG_INF("sleep %d ...", i);
        sleep(1);
    }

    return 0;
}