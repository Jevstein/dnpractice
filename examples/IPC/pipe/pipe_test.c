/*
 *  pipe_test.c 
 *  pipe_test
 *
 *  Created by Jevstein on 2018/10/29 11:18.
 *  Copyright @ 2018year Jevstein. All rights reserved.
 *
 *  管道
 */
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>


#define MAX_MSG_SIZE 1024

int main(int argc, char** argv)
{
    pid_t pid = -1;
    int pipefd[2] = {0};
   
    /**
     * 创建的一个pipe会有两个文件描述符，pipefd[0]是读取数据的，pipefd[1]是写入数据的。
     */
    if (0 != pipe(pipefd))
    {
        printf("failed to create pipe with errno = %d.\n", errno);
        return 0;
    }
    
    pid = fork();

    if (pid < 0)
    {
        printf("failed to call fork.\n");
    }
    /**
     * 这是父进程，如果我们要测试子进程发送数据给父进程，则父进程需要关闭写入端（pipefd[1]），
     * 而子进程需要关闭读取端(pipefd[0])
     */
    else if (pid > 0) // this is parent process
    {//父进程：读
        char msg[MAX_MSG_SIZE] = {0};
        close(pipefd[1]);
        read(pipefd[0], msg, MAX_MSG_SIZE);
        printf("we recved : %s.\n", msg);
    }
    else if (pid == 0)
    {//子进程：写
        char* wmsg = "hello everybody!!!";
        close(pipefd[0]);
        write(pipefd[1], wmsg, strlen(wmsg));
    }

	//close(pid);

    printf("game over! pid=%d\n", getpid());

    return 0;
}

//compile:
// $ gcc -o ../../../bin/pipe_test pipe_test.c