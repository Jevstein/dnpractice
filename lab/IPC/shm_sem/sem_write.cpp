/*
 *  sem_write.cpp 
 *  sem_write
 *
 *  Created by Lee/Jevstein on 2018/10/29 11:00.
 *  Copyright @ 2018year Jevstein. All rights reserved.
 *
 *  信号量-共享内存: 写
 */

#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <sys/sem.h>
#include <sys/types.h>

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

    //创建信号量
    int sem_id = semget(SEM_KEY, 1, 0666 | IPC_CREAT);
    if (sem_id == -1)
    {
        printf("failed to create sem with error=%s.", strerror(errno));
        return -1;
    }

    //初始化信号量
    semun sem_union;
    sem_union.val = 1;
    if(semctl(sem_id, 0, SETVAL, sem_union) == -1)
    {
         printf("failed to init sem with error=%s.", strerror(errno));
         // 删除信号量
         semctl(sem_id, 0, IPC_RMID, sem_union);
         return -1;
    }

    pid_t pid = 0;
    // 开启多个进程
    for(int i = 0; i < 4; i++)
    {
        pid_t pid = fork();
        if (pid == 0)
        {
            break;
        } 
    }

    // 父进程
    if (pid > 0)
    {
        for(;;);
    }
 
    while(1)    
    {
        //等待信号量, 即执行P操作
        struct sembuf sem_buffer;
        sem_buffer.sem_num = 0;
        sem_buffer.sem_op = -1;//P操作
        sem_buffer.sem_flg = SEM_UNDO;
        if(semop(sem_id, &sem_buffer, 1) == -1)
        {
			printf("wait sem failed with error=%s.\n", strerror(errno));
			return -1;
        }

        shared_buffer_t* shared = (shared_buffer_t*)shared_buffer_ptr;
        const char* msg = "lee ge stay alone, please contact me with my LINE : leege.\n";
        strcpy(shared->buffer, msg);
    
        shared->written = 1;
        // 已经写完，离开临界区
        sem_buffer.sem_op = 1;
        if(semop(sem_id, &sem_buffer, 1) == -1)
        {
            printf("leave sem failed with error=%s\n", strerror(errno));
            return -1;
        }
        usleep(100000);  /*100 毫秒*/
    }

    //把共享内存从当前进程中分离
    if(shmdt(shared_buffer_ptr) == -1)
    {
		fprintf(stderr, "dettaches shared buffer failed.\n");
		return -1;
    }

    //释放信号量
    if(semctl(sem_id, 0, IPC_RMID, sem_union) == -1)
    {
        printf("release sem failed with error=%s.\n", strerror(errno));
        return -1;
    }

    return 0 ;
}

//compile:
// $ g++ -o ../../../bin/shm_sem_wr sem_write.cpp