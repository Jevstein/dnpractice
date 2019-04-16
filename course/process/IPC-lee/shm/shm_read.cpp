/*
 *  shm_read.cpp 
 *  shm_read
 *
 *  Created by Lee/Jevstein on 2018/10/29 10:57.
 *  Copyright @ 2018year Jevstein. All rights reserved.
 *
 *  1.共享内存(shm): 读
 *		shm_get,shm_at,shm_dt,shm_ctl
 *
 *  2.用法:
 *		1）int shmget(key_t key, size_t size, int shmflg);//在物理内存创建一个共享内存，返回共享内存的编号。
 *		2）void *shmat(int shmid, constvoid shmaddr,int shmflg);//连接成功后把共享内存区对象映射到调用进程的地址空间
 *		3）void *shmdt(constvoid* shmaddr);//断开用户级页表到共享内存的那根箭头。
 *		4）int shmctl(int shmid, int cmd, struct shmid_ds* buf);//释放物理内存中的那块共享内存。
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