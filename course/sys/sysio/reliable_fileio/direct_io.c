/**
 * 直接文件IO：越过文件系统
 *       缺点：慢
 * 
*/
#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUF_SIZE  512
int debug = 0;

int main(int argc, char ** argv)
{
    char *buf = NULL; 
    const char * filename = "./write.txt";
    int fd = -1;
    time_t start,cur;
    int rlen = 0,ret = 0;
    static int read_total = 0;
    
    //ret = (char *)malloc(&buf,BUF_SIZE);  
    ret = posix_memalign((void **)&buf, 512, BUF_SIZE);//非512不可！
    if(ret) fprintf(stderr,"posix_memalign failed. reason: %s\n",strerror(errno));

    start = time(NULL);

    do {
		read_total ++;
        //fd = open(filename, O_RDWR|O_DIRECT);
        fd = open(filename, O_RDWR);
        if(fd<0)
        {
            fprintf(stderr, "fopen %s failed, reason: %s. \nexit.\n",filename,strerror(errno));
	        return -1;
        }
    	
        do {
            if((rlen = read(fd,buf,BUF_SIZE)) < 0) {
                fprintf(stderr, "read from %s failed, reason: %s. \nexit.\n", filename, strerror(errno));
            }

            if(debug) printf("read: %d\n",rlen);
        } while(rlen>0);

        printf(" finished.\n");

        close(fd);
        cur = time(NULL);
    } while((cur-start) < 20);

    printf("total num: %d\n",read_total);
    return 0;
}
