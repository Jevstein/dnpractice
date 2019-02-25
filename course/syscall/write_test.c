#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define TOTAL_SIZE (1024*1024*500)
#define BUF_SIZE  (8192)

int main(int argc, char ** argv)
{
    char buffer[BUF_SIZE];
    const char * filename = "./write.txt";

    int fd = -1;
    int i = 0;

    memset(buffer,'8',BUF_SIZE);

    fd = open(filename, O_RDWR|O_TRUNC|O_CREAT);
    if(fd<0)
    {
        fprintf(stderr, "fopen %s failed, reason: %s. \nexit.\n",filename,strerror(errno));
        return -1;;
    }

    int num = TOTAL_SIZE/BUF_SIZE;
    for( i=0; i<num; i++)
    {
        //sleep(1);
        if(write(fd,buffer,BUF_SIZE) < 0)
        {
            fprintf(stderr, "write to %s failed, reason: %s. \nexit.\n", filename, strerror(errno));
			exit(-1);
        }

    }

    close(fd);
    return 0;
}
