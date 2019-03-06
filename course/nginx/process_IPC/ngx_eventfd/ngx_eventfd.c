#include <stdlib.h>
#include <stdio.h>
#include <sys/eventfd.h>
#include <pthread.h>
#include <memory.h>
#include <unistd.h>
#include <errno.h>
#include <stdint.h>
#include <time.h>

// log
#define LOG_ERR(fmt,...) { time_t now = time(NULL); printf("[%.24s][error][%d] "fmt" ["__FILE__":%s().%d]\n", ctime(&now), getpid(), ##__VA_ARGS__, __FUNCTION__, __LINE__); }
#define LOG_EXP(fmt,...) { time_t now = time(NULL); printf("[%.24s][exception][%d] "fmt" ["__FILE__":%s().%d]\n", ctime(&now), getpid(), ##__VA_ARGS__, __FUNCTION__, __LINE__); }
#define LOG_WAR(fmt,...) { time_t now = time(NULL); printf("[%.24s][warning][%d] "fmt"\n", ctime(&now), getpid(), ##__VA_ARGS__); }
#define LOG_INF(fmt,...) { time_t now = time(NULL); printf("[%.24s][inf][%d] "fmt"\n", ctime(&now), getpid(), ##__VA_ARGS__); }
#define LOG_DBG(fmt,...) { time_t now = time(NULL); printf("[%.24s][dbg][%d] "fmt"\n", ctime(&now), getpid(), ##__VA_ARGS__); }


int event_fd__ = -1;

//循环接收线程: 
void* recv(void * pars) {
    uint64_t msg = 0;
    int len;

    LOG_INF("thread of receiving created!");
    while(1) {
        len = read(event_fd__, &msg, sizeof(uint64_t)); //若计数器为0, 则阻塞
        LOG_INF("current msg is %ld, len=%d", msg, len);
    }
}

int main(int argc, char ** argv) {
    pthread_t tid;
    pid_t fpid;
    int len = -1;
    static uint64_t item = 1;

    event_fd__ = eventfd(0, 0);
    if(event_fd__ == -1) {
        LOG_ERR("failed to create event fd!");
    } else {
        LOG_INF("success to create event fd[%d]", event_fd__);
    }
    fpid = fork();
    if(fpid > 0) {  //父进程接收消息（父进程同时也发送消息。）
        pthread_create(&tid, NULL, recv, NULL);
    }

    //循环发送:
    while(1) {
        sleep(2);
        ++item;

        //若写sizeof(unsigned int)，则参数错误。必须传8。
        //若计数器达到0xfffffffe，则阻塞
        len = write(event_fd__, &item, sizeof(uint64_t)); 
        if(len != sizeof(uint64_t)) {
            LOG_ERR("failed to write event fd, errno: %d, errmsg: %s" ,errno, strerror(errno));
        } else {
            LOG_INF("success to write: len=%d", len);
        }
    }
    pthread_exit(0);
    return 0;
}
