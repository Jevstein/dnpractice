/**
 * 
 * pthread_once：“单例” - 多个线程调用，但只执行一次
 * 
*/
#include<stdio.h>
#include<pthread.h>

pthread_once_t once=PTHREAD_ONCE_INIT;

void run(void)
{
    printf("Function run is running in thread %u\n",pthread_self());
}

void *thread1(void)
{
    pthread_t tid=pthread_self();
    printf("current thread's ID is %u\n",tid);
    pthread_once(&once,run);
    printf("thread1 ends\n");
}

void *thread2(void)
{
    pthread_t tid=pthread_self();
    printf("current thread's ID is %u\n",tid);
    pthread_once(&once,run);
    printf("thread2 ends\n");
}

int main()
{
    pthread_t thid1,thid2;
    pthread_create(&thid1,NULL,thread1,NULL);
    pthread_create(&thid2,NULL,thread2,NULL);
    sleep(3);
    printf("main thread exit!\n");
    exit(0);
}
