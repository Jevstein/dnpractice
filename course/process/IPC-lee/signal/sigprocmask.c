
/**
 * 来自: https://blog.csdn.net/beginning1126/article/details/8680757 
 * 
 *  注意观察运行结果，在sleep的时候，按多次“ctrl+\”，由于sleep之前block了SIG_QUIT，
 * 所以无法获得SIG_QUIT，但是一旦运行sigprocmask(SIG_SETMASK, &old, NULL);
 * 则unblock了SIG_QUIT，则之前发送的SIG_QUIT随之而来。
 *
 * 由于信号处理函数中设置了DFL，所以再发送SIG_QUIT，则直接coredump！
 * 
 */
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
 
static void sig_quit(int signo)
{
    printf("catch SIGQUIT\n");
    signal(SIGQUIT, SIG_DFL);
}
 
int main (void)
{
    sigset_t new, old;//, pend;
    
    signal(SIGQUIT, sig_quit);
 
    sigemptyset(&new);
    sigaddset(&new, SIGQUIT);
    sigprocmask(SIG_BLOCK, &new, &old);//此时“ctrl+\”无效，被阻塞
 
    sleep(5);
 
    printf("SIGQUIT unblocked\n");
    sigprocmask(SIG_SETMASK, &old, NULL);//解除阻塞，“ctrl+\”退出
 
    sleep(50);
    printf("the end\n");

    return 1;
}
