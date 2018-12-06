#include <iostream>
#include <stdlib.h> 
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>
 
int num = 0;
int MAX_THREAD_NUM = 4;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

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
        pthread_mutex_lock(&mutex);

        ++num;  

        pthread_mutex_unlock(&mutex);
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
    pthread_t tid[MAX_THREAD_NUM];
    for(int i = 0; i < MAX_THREAD_NUM; i++)
    {
        pthread_create(&tid[i], NULL, thread_proc, &loop_count);
    }

    for (int i = 0; i < MAX_THREAD_NUM; i++)
    {
        pthread_join(tid[i], NULL);
    }
 
    time_t end = get_current_timestamp();
    std::cout<<"num:"<<num<<std::endl;
    std::cout<<"cost:"<<end-start<<std::endl;
 
    pthread_mutex_destroy(&mutex);
 
    return 0;
}

