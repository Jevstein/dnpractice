/**
 * 
 * 伪共享
 * 
 * 注：程序中的LEVEL1_DCACHE_LINESIZE宏来自g++编译命令传入的，使用Shell命令
 * getconf LEVEL1_DCACHE_LINESIZE能获取cpu cache line的大小, 见makefile:
 * LEVEL1_DCACHE_LINESIZE = $(shell getconf LEVEL1_DCACHE_LINESIZE)
*/
#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <pthread.h>

#define PACK  __attribute__  ((packed))
typedef int cache_line_int __attribute__((aligned(LEVEL1_DCACHE_LINESIZE)));

typedef struct _data data;

struct _data
{
    cache_line_int a;
    cache_line_int b;
};

/*
struct data
{
    int a;
    int b;
};
*/

#define MAX_NUM 500000000

void* thread_func_1(void* param)
{
    struct timeval start, end;
    gettimeofday(&start, NULL);
    data* d = (data*)param;
    for (int i=0; i<MAX_NUM; ++i)
    {
        ++d->a;
    }
    gettimeofday(&end, NULL);
    printf("thread 1, time=%d\n", (int)(end.tv_sec-start.tv_sec)*1000000+(int)(end.tv_usec-start.tv_usec));
    return NULL;
}

void* thread_func_2(void* param)
{
    struct timeval start, end;
    gettimeofday(&start, NULL);
    data* d = (data*)param;
    for (int i=0; i<MAX_NUM; ++i)
    {
        ++d->b;
    }
    gettimeofday(&end, NULL);
    printf("thread 2, time=%d\n", (int)(end.tv_sec-start.tv_sec)*1000000+(int)(end.tv_usec-start.tv_usec));
    return NULL;
}

int main()
{
    data d = {a:0, b:0};
    pthread_t t1, t2;
    pthread_create(&t1, NULL, thread_func_1, &d);
    pthread_create(&t2, NULL, thread_func_2, &d);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    printf("end, a=%d,b=%d\n", d.a, d.b);
    return 0;
}

/*
g++ -o test_false_sharing_2 test_false_sharing_2.cpp -g -Wall -lpthread -DLEVEL1_DCACHE_LINESIZE=`getconf LEVEL1_DCACHE_LINESIZE`
*/

/*
��������������2.5��
thread 1, time=1607430
thread 2, time=1629508
*/
