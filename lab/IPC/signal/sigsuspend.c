/**
 * 来自: http://blog.sina.com.cn/s/blog_6af9566301013xp4.html
 * 
 * sigsuspend的原子操作是：
 *（1）设置新的mask阻塞当前进程(上面是用wait替换new，即阻塞SIGUSR1信号)
 *（2）收到SIGUSR1信号，阻塞，程序继续挂起；收到其他信号，恢复原先的mask(即包含SIGINT信号的)。
 *（3）调用该进程设置的信号处理函数(程序中如果先来SIGUSR1信号，然后过来SIGINT信号，则信号处理函数会调用两次，
 *     打印不同的内容。第一次打印SIGINT,第二次打印SIGUSR1，因为SIGUSR1是前面阻塞的)
 *（4）待信号处理函数返回，sigsuspend返回了。(sigsuspend将捕捉信号和信号处理函数集成到一起了)
 * 
*/
// #include <unistd.h>
// #include <signal.h>
// #include <stdio.h>
#include "header.h"

//信号处理程序
void handler(int sig)
{
   // if (sig == SIGINT)
   //    LOG_INF("SIGINT sig");
   // else if (sig == SIGQUIT)
   //    LOG_INF("SIGQUIT sig");
   // else
   //    LOG_INF("SIGUSR1 sig");

   switch (sig)
   {
   case SIGINT:   LOG_INF("[handler]: SIGINT sig");  break;
   case SIGQUIT:  LOG_INF("[handler]: SIGQUIT sig"); break;
   case SIGUSR1:  LOG_INF("[handler]: SIGUSR1 sig"); break;
   default:       LOG_ERR("[handler]: other sig=%d", sig);
      break;
   }
}

int main()
{
   sigset_t new,old,wait;   //三个信号集
   struct sigaction act;
   act.sa_handler = handler;
   sigemptyset(&act.sa_mask);
   act.sa_flags = 0;

   //可以捕捉以下三个信号：SIGINT/SIGQUIT/SIGUSR1
   sigaction(SIGINT, &act, 0);     //"ctrl + c"
   sigaction(SIGQUIT, &act, 0);    //"Ctrl+ \"
   sigaction(SIGUSR1, &act, 0);    //"kill -SIGUSR1 <pid>""
   //注：其它信号
   // SIGTERM: "kill 默认不带参数"
   // SIGKILL："kill -9 <pid>" - 不可忽略
   // SIGSTOP： - 不可忽略

   sigemptyset(&new);
   sigaddset(&new, SIGINT);  //SIGINT信号加入到new信号集中

   sigemptyset(&wait);
   sigaddset(&wait, SIGUSR1);  //SIGUSR1信号加入wait

   sigprocmask(SIG_BLOCK, &new, &old);//将SIGINT阻塞，保存当前信号集到old中

   LOG_INF("Before sigsuspend");

   // 临界区代码执行：
   // 程序在此处挂起；用wait信号集替换new信号集。 即：
   //  1.过来SIGUSR1信号(&wait)，阻塞掉，程序继续挂起；
   //  2.过来其他信号，如SIGINT(&new)，则会唤醒程序。执行sigsuspend的原子操作。
   //  注意：如果“sigaddset(&wait, SIGUSR1);”这句没有，则此处不会阻塞任何信号，即过来任何信号均会唤醒程序。
   if (sigsuspend(&wait) != -1)//sigsuspend实际是将sigprocmask和pause结合起来原子操作
      LOG_ERR("sigsuspend error");
      
   LOG_INF("After sigsuspend");

   sigprocmask(SIG_SETMASK, &old, NULL);

   // sleep(20);
   LOG_INF("the end!");

   return 0;
}