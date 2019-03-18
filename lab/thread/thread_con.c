/**
 * 1.下面情况适合用pthread_cond_broadcast
 *      A.一个生产者多消费者，生产者能一次产生多个产品的情况。
 *      B.多生产者多消费者
 *      C.读写锁实现（写入之后，通知所有读者）
 *
 *  2.下面情况适合pthread_cond_signal的情况
 *      单一生产者，生产者一次生产一个产品的情况，最好一个消费者
 *  注意：pthread_cond_signal在单一异步唤醒的处理线程的情况时，是不安全的
 * 
*/
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

static pthread_cond_t cond;
static pthread_mutex_t mutex1;
static pthread_mutex_t mutex2;
void *thread1_entry(void *arg)
{
    while(1)
    {
        pthread_mutex_lock(&mutex1);
        printf("[T1]: cond wait cond1\n");
        pthread_cond_wait(&cond, &mutex1);
        printf("[T1]: recv cond1\n");
        pthread_mutex_unlock(&mutex1);
    }
}

void *thread2_entry(void *arg)
{
    while(1)
    {
        pthread_mutex_lock(&mutex1);
        printf("[T2]: cond wait cond2\n");
        pthread_cond_wait(&cond, &mutex1);
        printf("[T2]: recv cond2\n");
        pthread_mutex_unlock(&mutex1);
    }
}

void *thread3_entry(void *arg)
{
    int ret;
    while(1)
    {
        pthread_mutex_lock(&mutex1);
        pthread_mutex_lock(&mutex2);
        ret = pthread_cond_broadcast(&cond);
        // ret = pthread_cond_signal(&cond);
        printf("[T3]: pthread_cond_broadcast\n");
        if(ret < 0)
        {
            printf("pthread_cond_broadcast error\n");
        }
        pthread_mutex_unlock(&mutex2);
        pthread_mutex_unlock(&mutex1);
        sleep(2);
    }
}

int main(void)
{
    int ret = 0;
    pthread_t tid1, tid2, tid3;
    ret = pthread_cond_init(&cond, NULL);
    if (ret < 0) printf("pthread_cond_init error\n");

    ret = pthread_mutex_init(&mutex1, NULL);
    if (ret < 0) printf("pthread_mutex_init1 error\n");

    ret = pthread_mutex_init(&mutex2, NULL);
    if (ret < 0) printf("pthread_mutex_init2 error\n"); 

    ret = pthread_create(&tid1, NULL, thread1_entry, NULL);
    if (ret < 0) printf("pthread_create thread1 error\n");

    ret = pthread_create(&tid2, NULL, thread2_entry, NULL);
    if (ret < 0) printf("pthread_create thread2 error\n");

    sleep(2);
    ret = pthread_create(&tid3, NULL, thread3_entry, NULL);
    if (ret < 0) printf("pthread_create thread3 error\n");

#if 0
    pthread_mutex_lock(&mutex1);
    pthread_mutex_lock(&mutex2);
    ret = pthread_cond_broadcast(&cond);
    if(ret < 0) printf("pthread_cond_broadcast error\n");
    pthread_mutex_unlock(&mutex1);
    pthread_mutex_unlock(&mutex2);
#endif

    while(1)
    {
        sleep(10000);
    }
    return 0;
}