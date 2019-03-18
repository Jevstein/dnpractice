#include <stdio.h>
#include <unistd.h>
#include <errno.h>  
#include <string.h>
#include <pthread.h>

static void* thread_proc(void *p)
{
    int count = 10;
    while(1) {
        if (count <= 0)
            break;
        fprintf(stdout, "thread cbk[%3.3d][%p] ...\n", count--, p);
        usleep(1000 * 200);
    }

    fprintf(stdout, "the thread exits implicitly! \n");

    return NULL;
}

int main()
{
    printf("========= begin =========\n");
    pthread_t tid;
    int ret = pthread_create(&tid, NULL, &thread_proc, NULL);
    if (ret == 0) {
        if (pthread_join(tid, NULL) != 0)
            fprintf(stderr, "failed join thread!\n");
    }
    else {
        fprintf(stderr, "failed create thread!\n");
    }


    printf("========= the end =========\n");

    return 0;
}