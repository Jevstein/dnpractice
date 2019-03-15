/**
 * 定义函数: int sigaction(int signum,const struct sigaction *act ,struct sigaction *oldact);
 * 函数说明: sigaction()会依参数signum指定的信号编号来设置该信号的处理函数。参数signum可以指定SIGKILL和SIGSTOP以外的所有信号。
 * 如参数结构sigaction定义如下:
    struct sigaction
    {
        void (*sa_handler) (int);
        sigset_t sa_mask;
        int sa_flags;
        void (*sa_restorer) (void);
    }
 * signum参数指出要捕获的信号类型，act参数指定新的信号处理方式，oldact参数输出先前信号的处理方式（如果不为NULL的话）。
 * 
 * https://blog.csdn.net/weibo1230123/article/details/81411827
 * 
 * https://www.cnblogs.com/davidwang456/p/3519981.html
 * http://pubs.opengroup.org/onlinepubs/007908775/xsh/signal.h.html
 * http://pubs.opengroup.org/onlinepubs/007908775/xsh/sigaction.html
*/

#include "header.h"
#include <errno.h>

void usage1();

void usage2_show_handler(int sig);
void usage2();

void usage3_sig_usr(int signum);
void usage3();

/////////////////////////////////////////////////////////////////////////
void usage1()
{
    struct sigaction newact, oldact;
 
    /* 设置信号忽略 */
    newact.sa_handler = SIG_IGN; //这个地方也可以是函数
    sigemptyset(&newact.sa_mask);
    newact.sa_flags = 0;
    int count = 0;
    pid_t pid = 0;
 
    sigaction(SIGINT, &newact, &oldact);//原来的备份到oldact里面
 
    pid = fork();
    if (pid == 0)
    {//child
        while (1)
        {
            LOG_INF("I'm child......\n");
            sleep(1);
        }
    }
    else
    {//parrent
        while (1)
        {
            if (count++ > 3)
            {
                sigaction(SIGINT, &oldact, NULL);//备份回来
                LOG_INF("kill child: pid=%d", pid);
                kill(pid, SIGKILL); //父进程发信号，来杀死子进程
            }
    
            LOG_INF("I am father ......\n");
            sleep(1);
        }
    }
}

/////////////////////////////////////////////////////////////////////////
void usage2_show_handler(int sig)
{
    LOG_INF("[hander]: I got signal: sig=%d", sig);
    int i;
    for(i = 0; i < 5; i++) 
    {
        LOG_INF("[hander]: i=%d", i);
        sleep(1);
    }
}
 
void usage2()
{
    int i = 0;
    struct sigaction act, oldact;
    act.sa_handler = usage2_show_handler;
    sigaddset(&act.sa_mask, SIGQUIT);
    act.sa_flags = SA_RESETHAND | SA_NODEFER;
    //act.sa_flags = 0;
 
    sigaction(SIGINT, &act, &oldact);
    while(1) 
    {
        sleep(1);
        LOG_INF("[usage2]: sleeping %d", i);
        i++;
    }
}

/////////////////////////////////////////////////////////////////////////
void usage3_sig_usr(int signum)
{
    if(signum == SIGUSR1)
    {
        LOG_INF("[sig]: SIGUSR1 received");
    }
    else if(signum == SIGUSR2)
    {
        LOG_INF("[sig]: SIGUSR2 received");
    }
    else
    {
        LOG_INF("[sig]: signal %d received", signum);
    }
}
 
void usage3()
{
    char buf[512];
    int n;
    struct sigaction sa_usr;
    sa_usr.sa_flags = 0;
    sa_usr.sa_handler = usage3_sig_usr;   //信号处理函数
    
    sigaction(SIGUSR1, &sa_usr, NULL);
    sigaction(SIGUSR2, &sa_usr, NULL);
    
    LOG_INF("[usage3]: My PID is %d", getpid());
    
    while (1)
    {
        if ((n = read(STDIN_FILENO, buf, 511)) == -1)
        {
            if (errno == EINTR)
            {
                LOG_INF("[usage3]: read is interrupted by signal");
            }
        }
        else
        {
            buf[n] = '\0';
            LOG_INF("[usage3]: %d bytes read: %s", n, buf);
        }
    }
}

int main()
{
    ////1.忽略信号: 忽略信号SIGINT(Ctrl + c)，直到执行了sigaction(SIGINT, &oldact, NULL);
    // usage1();

    //2.忽略信号:
    // 信号SIGINT(Ctrl + c)的信号处理函数show_handler执行过程中，本进程收到信号SIGQUIT(Crt+\)，
    // 将阻塞该信号，直到show_handler执行结束才会处理信号SIGQUIT
    // usage2();

    //3.
    // kill -USR1 5904
    // kill -USR2 5904
    usage3();

    return 0;
}