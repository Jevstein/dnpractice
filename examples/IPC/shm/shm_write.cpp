/*
 *  shm_write.cpp 
 *  shm_write
 *
 *  Created by Lee/Jevstein on 2018/10/29 10:57.
 *  Copyright @ 2018year Jevstein. All rights reserved.
 *
 *  共享内存(shm): 写
 */

#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

#include "shm_data.h"


int main(int argc, char** argv)
{
    int shared_buffer_id = shmget(SHARED_BUFFER_KEY, sizeof(shared_buffer_t), 0666 | IPC_CREAT );
    if (shared_buffer_id == -1)
    {
        printf("create shared buffer failed with error = %s.\n", strerror(errno));
        return -1;
    }

    /* 将创建的共享内存映射到当前进程的地址空间 */
    void* shared_buffer_ptr = shmat(shared_buffer_id, (void*)0, 0);
    if ((void*)-1 == shared_buffer_ptr)
    {
        printf("attaches shared buffer failed with error=%s.\n", strerror(errno));
        return -1;
    }

    shared_buffer_t* shared = (shared_buffer_t*)shared_buffer_ptr;
    // 如果不可以写，则阻塞住 --->工程中应该采用信号量加锁
    while (0 != shared->written)
    {
        sleep(1);
    }

    const char* msg = "lee ge stay alone, please contact me with my LINE : leege.\n";
    strcpy(shared->buffer, msg);
    shared->written = 1;

    //把共享内存从当前进程中分离
    if(shmdt(shared_buffer_ptr) == -1)
    {
		fprintf(stderr, "dettaches shared buffer failed.\n");
		return -1;
    }

    return 0 ;
}

//compile:
// $ g++ -o ../../../bin/shm_wr shm_write.cpp