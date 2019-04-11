/**
 * Martin: 无fsync引发的血案 - 重要邮件文件丢失
 * 
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define TOTAL  10

int main(int argc, char ** argv)
{
    const char * TEXT = "This is a test.\n";
    const char * filename = "./write.txt";
    int fd = -1;
    int i = 0;

    fd = open(filename, O_RDWR|O_TRUNC|O_CREAT);
    if(fd<0)
    {
        fprintf(stderr, "fopen %s failed, reason: %s. \nexit.\n",filename,strerror(errno));
	    return -1;;
    }
    
    for( i=0; i<TOTAL; i++)
    {
        //sleep(1);
        if(writeToFile(fd,TEXT,strlen(TEXT)) < 0)
        {
            fprintf(stderr, "write to %s failed, reason: %s. \nexit.\n", filename, strerror(errno));
        }

        printf(" %d\n",i+1);
    }
    printf(" finished.\n");

#if 0//确保文件写入了磁盘
    //int ret = fsync(fd); //类似api如：fdatasync
    //if(ret ) fprintf(stderr,"write failed. reason: %s\n",strerror(errno));
#endif

    //注: 若不调用fsync()/fdatasync(), 此时进程意外关闭(如掉电)，会导致文件未写进磁盘
    //    虚拟机模拟掉电，现象：有文件名，但无内容

    printf("Start to sleep 30 seconds ......\n");
    sleep(30);

    close(fd);
    return 0;
}

int writeToFile(int fd, char * buf, int len)
{
    int wlen=0;
    if((wlen = write(fd, buf, len)) < 0)
    {
        fprintf(stderr, "write to %d failed, reason: %s. \n", fd, strerror(errno));
        return -1;
    }
    
    return wlen;
}
