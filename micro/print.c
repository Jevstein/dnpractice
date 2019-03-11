#include <stdio.h>
#include <errno.h>  
#include <string.h>

int main()
{
    {
        //在默认情况下，stdout是行缓冲的，他的输出会放在一个buffer里面，
        //只有到换行的时候，才会输出到屏幕。而stderr是无缓冲的，会直接输
        //出，举例来说就是printf(stdout, "xxxx") 和 printf(stdout, "xxxx\n")，
        //前者会憋住，直到遇到新行才会一起输出。而printf(stderr, "xxxxx")，不管有么有\n，都输出。
        fprintf(stdout, "[out] Hello ");
        fprintf(stderr, "[err] World!");
    }

    {// 定向输出： print.exe > tmp.txt 
        fprintf(stderr, "[err] Can't open it!\n"); //无法定向到文件
        fprintf(stdout, "[out] Can't open it!\n"); 
        printf("[def] Can't open it!\n"); 
    }

    {  
        FILE *fp;  
        if ((fp = fopen("tmp.txt", "r")) == NULL)  
        {  
            perror("perror");
            printf("strerror:%s\n", strerror(errno));  
        }
    }

    return 0;
}