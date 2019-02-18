/*
 *  fifo_write.c 
 *  fifo_write
 *
 *  Created by Lee/Jevstein on 2018/10/29 10:56.
 *  Copyright @ 2018year Jevstein. All rights reserved.
 *
 *  共享文件(FIFO队列): 写
 */
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>

#define FIFO_FILE_PATH  "/tmp/fifo_test"


int main(int argc, char** argv)
{
    if (-1 == access(FIFO_FILE_PATH, F_OK))
    {
        printf("fifo file is not exist, and try to create fifo file.\n");
        if (0 != mkfifo(FIFO_FILE_PATH, 0777))
        {
            printf("create fifo file failed with error : %s\n", strerror(errno));
            return -1;
        }
    }

    /*
     *  以只写方式打开FIFO文件，不能以读写方式打开FIFO，当然我们也可以设置为O_WRONLY | O_NONBLOCK，那么此时是
     *  以非阻塞的方式打开文件
     */
    int fd = open(FIFO_FILE_PATH, O_WRONLY);
    if (-1 == fd)
    {
        printf("open fifo file failed.\n");
        return -1;
    }

    char* msg = "sexy lady, what's your LINE number.\n";
    int len = strlen(msg);
    if( write(fd, msg, len) < len)
    {
        printf("only write ");
    }

	close(fd);

    //for(;;);

    return 0;
}

//compile:
// $ gcc -o ../../../bin/fifo_wr fifo_write.c