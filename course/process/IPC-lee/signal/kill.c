/*
 *  https://www.cnblogs.com/davidwang456/p/3519981.html
*/

#include "header.h"
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;
    int status;
    if(!(pid= fork())) {
        LOG_INF("Hi I am child process!");
        sleep(10);
        return 0;
    }
    else {
        LOG_INF("send signal to child process: pid=%d", pid);
        sleep(1);
        kill(pid, SIGABRT);
        wait(&status);
        if(WIFSIGNALED(status))
            LOG_INF("chile process receive signal: status=%d", WTERMSIG(status));
    }

    return 0;
}