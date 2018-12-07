#include <iostream>
#include <stdlib.h> 
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h> 

int num = 0;
int MAX_THREAD_NUM = 4;

time_t get_current_timestamp()
{
    struct timeval now = {0, 0};
    gettimeofday(&now, NULL);
    return now.tv_sec * 1000 * 1000 + now.tv_usec;
}
 
void* thread_proc(void* argv)
{
    int loop_count = *(int*)argv;
    for(int i=0; i < loop_count; i++)
    {
        __sync_fetch_and_add(&num, 1);
    } 

    return NULL;  
}
 
int main(int argc, char** argv)
{
    if(argc != 2)
    {
       std::cout<<"please input"<<argv[0]<<" loop num"<<std::endl;
    }

    time_t start = get_current_timestamp();
    int loop_count = atoi(argv[1]);

    cpu_set_t cpuset;
    pthread_t tid[MAX_THREAD_NUM];    

    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    //设置主线程在CPU0上
    pthread_t master_tid = pthread_self();
    CPU_ZERO(&cpuset);
    CPU_SET(0, &cpuset);
    pthread_setaffinity_np(master_tid, sizeof(cpu_set_t), &cpuset);
    for(int i = 0; i < MAX_THREAD_NUM; i++)
    {
        //将第i个线程绑定至第i + 1个core上执行, 因为CPU0上运行主线程
        CPU_ZERO(&cpuset);
        CPU_SET(i + 1, &cpuset);
        pthread_attr_setaffinity_np(&attr, sizeof(cpu_set_t), &cpuset);
        pthread_create(&tid[i], &attr, thread_proc, &loop_count);
    }

    for (int i = 0; i < MAX_THREAD_NUM; i++)
    {
        pthread_join(tid[i], NULL);
    }
 
    time_t end = get_current_timestamp();
    std::cout<<"num:"<<num<<std::endl;
    std::cout<<"cost:"<<end-start<<std::endl;
 
    return 0;
}

