/*
 *  sem_read.cpp 
 *  sem_read
 *
 *  Created by Lee/Jevstein on 2018/10/29 10:59.
 *  Copyright @ 2018year Jevstein. All rights reserved.
 *
 *  信号量-共享内存: 读
 */

#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/sem.h>

#include "sem_data.h"


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
    /* 通知对端，我已经可以读数据了，你现在可以写入数据了 */
    //创建信号量
    int sem_id = semget(SEM_KEY, 1, 0666 | IPC_CREAT);
    if (sem_id == -1)
    {
        printf("failed to create sem with error=%s.", strerror(errno));
        return -1;
    }

    //初始化信号量
    union semun sem_union;
    sem_union.val = 0;
    if(semctl(sem_id, 0, SETVAL, sem_union) == -1)
    {
         printf("failed to init sem with error=%s.", strerror(errno));
         // 删除信号量
         semctl(sem_id, 0, IPC_RMID, sem_union);
         return -1;
    }
    
    int index = 0;

    while(1)
    {
        // 等待信号量
        struct sembuf sem_buffer;
        sem_buffer.sem_num = 0;
        sem_buffer.sem_op = -1;//P操作: -1, if (==0) 阻塞
        sem_buffer.sem_flg = SEM_UNDO;
        if(semop(sem_id, &sem_buffer, 1) == -1)
        {
            printf("failed to wait sem with error=%s.\n", strerror(errno));
            return -1;
        }
   
        // 如果非0，则可以读取内容
        if (0 != shared->written)
        {
            char msg[MAX_MSG_SIZE] = {0};
            strcpy(msg, shared->buffer);
            shared->written = 0;
            printf("recved content is : %s, index = %d.\n", msg, index);
            index ++;
            shared->written = 0;
        }

        // 发送信号量，离开临界区
        sem_buffer.sem_op = 1;//V操作: +1
        if(semop(sem_id, &sem_buffer, 1) == -1)
        {
            printf("failed to leave sem with error=%s\n", strerror(errno));
            return -1;
        }
    }

    //把共享内存从当前进程中分离
    if(shmdt(shared_buffer_ptr) == -1)
    {
		fprintf(stderr, "dettaches shared buffer failed.\n");
		return -1;
    }

    //删除共享内存
    if(shmctl(shared_buffer_id, IPC_RMID, 0) == -1)
    {
		fprintf(stderr, "remove shared buffer failed.\n");
		return -1;
    } 

    return 0 ;
}

//compile:
// $ g++ -o ../../../bin/shm_sem_rd sem_read.cpp