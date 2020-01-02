/*
 *  entry.c 
 *
 *  Created by Jevstein on 2020/01/01 22:20.
 *  Copyright @ 2020year Jevstein. All rights reserved.
 *
 *  mini_crt测试
 * [简介]：
 *      APP的程序运行入口为main函数，而main函数却是由运行库（Glibc、MSVC RCT）最初调用的。所以首先要
 * 确定Min CRT的入口函数，它得至少负责三部分工作：1.准备好程序运行环境及完成CRT的初始化；2.调用main函数
 * 执行程序主题；3.清理程序运行后的各种资源。其次，运行库为所有程序提供的入口函数应该相同，在链接程序时要
 * 指定该入口函数名。Mini CRT的入口函数约定为：void mini_crt_entry(void)
 * 
 * [编译]：
 * 1.linux编译：
 *     $gcc -c -ggdb -fno-builtin -nostdlib -fno-stack-protector *.c
 *     $ld -static -e mini_crt_entry mini_crt/entry.o example1.o mini_crt/minicrt.a -o example1
 * 
 * 2.windows编译：
 *     $cl /c /DWIN32 *.c
 *     $link example1.obj mini_crt/minicrt.lib kernel32.lib /NODEFAULTLIB /entry:mini_crt_entry
 * 
 */
#include "mini_crt/mini_crt.h"

int main(int argc, char *argv[])
{
    int i;
    FILE *fp;
    char **v = malloc(argc * sizeof(char *));

    for (i = 0; i < argc ; ++i) {
        v[i] = malloc(strlen(argv[i]) + 1);
        strcpy(v[i], argv[i]);
    }

    fp = fopen("test.txt", "w");
    for (i = 0; i < argc; ++i) {
        int len = strlen(v[i]);
        fwrite(&len, 1, sizeof(int), fp);
        fwrite(v[i], 1, len, fp);
    }
    fclose(fp);

    fp = fopen("test.txt", "r");
    for (i = 0; i < argc; ++i) {
        int len;
        char *buf;

        fread(&len, 1, sizeof(int), fp);
        buf = malloc(len + 1);

        fread(buf, 1, len, fp);
        buf[len] = '\0';

        printf("%d %s\n", len, buf);
        free(buf);
        free(v[i]);
    }
    fclose(fp);
}