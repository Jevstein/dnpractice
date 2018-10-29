/*
 *  shm_read.cpp 
 *  shm_read
 *
 *  Created by Lee/Jevstein on 2018/10/29 10:57.
 *  Copyright @ 2018year Jevstein. All rights reserved.
 *
 *  共享内存(shm): 读
 *		shm_get,shm_at,shm_dt,shm_ctl
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
        printf("failed to create shared buffer with error = %s.\n", strerror(errno));
        return -1;
    }

    /* 将创建的共享内存映射到当前进程的地址空间 */
    void* shared_buffer_ptr = shmat(shared_buffer_id, (void*)0, 0);
    if ((void*)-1 == shared_buffer_ptr)
    {
        printf("failed to attach shared buffer with error=%s.\n", strerror(errno));
        return -1;
    }

    shared_buffer_t* shared = (shared_buffer_t*)shared_buffer_ptr;
    /* 设置共享内存为可写状态 */
    shared->written = 0;
    // 如果工程内存可写，则等待 --->工程中应该采用信号量加锁
    while (0 == shared->written)
    {
        sleep(1);
    }

    char msg[MAX_MSG_SIZE] = {0};
    strcpy(msg, shared->buffer);
    shared->written = 0;
    printf("recved content is : %s.\n", msg);

    //把共享内存从当前进程中分离
    if(shmdt(shared_buffer_ptr) == -1)
    {
		fprintf(stderr, "dettaches shared buffer failed.\n");
		return -1;
    }

    //删除共享内存
    if(shmctl(shared_buffer_id, IPC_RMID, 0) == -1)
    {
		fprintf(stderr, "failed to remove shared buffer.\n");
		return -1;
    } 

    return 0 ;
}

//compile:
// $ g++ -o ../../../bin/shm_rd shm_read.cpp