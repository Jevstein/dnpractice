/**
 * 
 * 线程的私有数据
 * 
 * int pthread_key_create(pthread_key_t *key, void (*destructor)(void*));
 *   第一个参数为指向一个键值的指针，
 *   第二个参数指明了一个destructor函数，如果这个参数不为空，那么当每个线程结束时，
 * 系统将调用这个函数来释放绑定在这个键上的内存块。
 * key一旦被创建，所有线程都可以访问它，但各线程可根据自己的需要往key中填入不同的值，
 * 这就相当于提供了一个同名而不同值的全局变量，一键多值。一键多值靠的是一个关键数据
 * 结构数组即TSD池，创建一个TSD就相当于将结构数组中的某一项设置为“in_use”，并将其索
 * 引返回给*key，然后设置清理函数。
 * 参考: https://www.cnblogs.com/zhangxuan/p/6515264.html
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

pthread_key_t key;

// void echomsg(int t)
// {//tx.ZhangFuchun
//     printf("destructor excuted in thread %d, param=%d\n", (int)pthread_self(), t);
// }

/*线程退出时释放私有数据空间, 注意主线程必须调用pthread_exit()(调用exit()不行)才能执行该函数释放accu指向的空间*/
void echo_destructor(void* t)
{//邶风
    printf("Thread %lx: freeing buffer at %p\n", pthread_self(), t);
    // free(t);
}

void* child1(void *arg)
{
    pthread_t tid = pthread_self();
    printf("thread %d enter\n", (int)tid);
    pthread_setspecific(key,(void *)tid);
    sleep(2);
    printf("thread %d returns %d\n", (int)tid, *(int*)pthread_getspecific(key));
    sleep(5);

    return NULL;
}

void* child2(void *arg)
{
    pthread_t tid = pthread_self();
    printf("thread %d enter\n", (int)tid);
    pthread_setspecific(key, (void *)tid);
    sleep(1);
    printf("thread %d returns %d\n", (int)tid, *(int*)pthread_getspecific(key));
    sleep(5);

    return NULL;
}

int main(void)
{
    pthread_t tid1, tid2;
    printf("hello\n");
    // pthread_key_create(&key, echomsg);
    // pthread_key_create(&key, NULL);
    pthread_key_create(&key, echo_destructor);
    pthread_create(&tid1,NULL,child1,NULL);
    pthread_create(&tid2,NULL,child2,NULL);
    sleep(10);
    pthread_key_delete(key);
    printf("main thread exit\n");
    
    return 0;
}