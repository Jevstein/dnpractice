/*
 *  entry.c 
 *
 *  Created by Jevstein on 2020/01/01 09:36.
 *  Copyright @ 2020year Jevstein. All rights reserved.
 *
 *  Mini CRT(模拟Glibc、MSVC CRT) - 入口函数
 * [简介]：
 *      APP的程序运行入口为main函数，而main函数却是由运行库（Glibc、MSVC RCT）最初调用的。所以首先要
 * 确定Min CRT的入口函数，它得至少负责三部分工作：1.准备好程序运行环境及完成CRT的初始化；2.调用main函数
 * 执行程序主题；3.清理程序运行后的各种资源。其次，运行库为所有程序提供的入口函数应该相同，在链接程序时要
 * 指定该入口函数名。Mini CRT的入口函数约定为：void mini_crt_entry(void)
 */
 #include "mini_crt.h"

#ifdef WIN32
#include <windows.h>
#endif

extern int main(int argc, char *argv[]);
void exit(int);

static void crt_fatal_error(const char *msg)
{
    // printf("fatal error: %s", msg);
    exit(1);
}

void mini_crt_entry(void)
{
    //e.g: tcp_clt.exe 192.168.0.95 6666

    int ret;

#ifdef WIN32
    int flag = 0;//引号标记
    int argc = 0;
    char* argv[16];//限定参数个数
    char* cl = GetCommandLineA();

    argv[0] = cl;
    argc++;
    while (*cl) {
        if (*cl == '\"') {
            flag = (flag == 0) ? 1 : 0;
        }
        else if ((*cl == ' ') && (flag == 0)) {
            if (*(cl + 1)) {
                argv[argc] = cl + 1;
                argc++;
            }
            *cl = "\0";
        }
        cl++;
    }
#else
    int argc;
    char **argv;

    char *ebp_reg = 0;
    //ebp_reg = %ebp
    asm("movl %%ebp, %0 \n":"=r"(ebp_reg));

    argc = *(int *)(ebp_reg + 4);
    argv = (char **)(ebp_reg + 8);
#endif

    if (!mini_crt_heap_init())
        crt_fatal_error("failed to initialize head!");

    if (!mini_crt_io_init())
        crt_fatal_error("failed to initialize IO!");

    ret = main(argc, argv);
    exit(ret);
}

void exit(int exit_code)
{
    //mini_crt_call_exit_routine();
#ifdef WIN32
    ExitProcess(exit_code);
#else
    asm("movl %0, %%ebx \n\t"
        "movl $1, %%eax \n\t"
        "int $0x80 \n\t"
        "hlt \n\t"::"m"(exit_code));
#endif
}