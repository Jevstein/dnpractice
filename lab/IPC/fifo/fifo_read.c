/*
 *  fifo_read.c 
 *  fifo_read
 *
 *  Created by Lee/Jevstein on 2018/10/29 10:55.
 *  Copyright @ 2018year Jevstein. All rights reserved.
 *
 * 共享文件(FIFO队列): 读
 */
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>

#define FIFO_FILE_PATH  "/tmp/fifo_test"
#define MAX_FIFO_MSG_SIZE  1024


int main(int argc, char** argv)
{
    if (-1 == access(FIFO_FILE_PATH, F_OK))
    {
        printf("fifo file is not exist, and try to create fifo file.\n");
    }
    
    int fd = open(FIFO_FILE_PATH, O_RDONLY);
    char buffer[MAX_FIFO_MSG_SIZE] = {0};
    int len = read(fd, buffer, MAX_FIFO_MSG_SIZE);
    if ( len <= 0 )
    {
        printf("read fifo file return nothing.\n");
        return -1;
    }

    printf("read msg result is : %s.\n", buffer);

	close(fd);

    return 0;
}

//compile:
// $ gcc -o ../../../bin/fifo_rd fifo_read.c