#include "header.h"
 
void handler(int sig)
{
    LOG_INF("Handle the signal: sig=%d", sig);
}
 
int main(int argc, char **argv)
{
    sigset_t sigset;    // 用于记录屏蔽字
    sigset_t ign;       // 用于记录被阻塞(屏蔽)的信号集
    struct sigaction act;
 
    // 清空信号集
    sigemptyset(&sigset);
    sigemptyset(&ign);
 
    // 向信号集中添加 SIGINT
    sigaddset(&sigset, SIGINT);
 
    // 设置处理函数 和 信号集
    act.sa_handler = handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(SIGINT, &act, 0);
 
    LOG_INF("Wait the signal SIGNAL...");
    pause();
 
    // 设置进程屏蔽字, 在本例中为屏蔽 SIGINT
    sigprocmask(SIG_SETMASK, &sigset, 0);
    LOG_INF("Please press Ctrl + C in 10 seconds...");
    sleep(10);
 
    // 测试 SIGINT 是否被屏蔽
    sigpending(&ign);
    if (sigismember(&ign, SIGINT))
    {
        LOG_INF("The SIGINT signal has ignored");
    }
 
    // 从信号集中删除信号 SIGINT
    sigdelset(&sigset, SIGINT);
    LOG_INF("Wait the signal SIGINT...");
 
    // 将进程的屏蔽字重新设置, 即取消对 SIGINT 的屏蔽
    // 并挂起进程
    sigsuspend(&sigset);
 
    LOG_INF("The app will exit in 5 secondes!");
    sleep(5);
 
    return 0;
}