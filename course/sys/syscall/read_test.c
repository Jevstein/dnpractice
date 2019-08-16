#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUF_SIZE  4096
#define BUF_SIZE_1  4

int main(int argc, char ** argv)
{
    char buffer[BUF_SIZE];
    const char * filename = "./write.txt";
    int fd = -1;
    int i = 0, len = 0;


    fd = open(filename, O_RDWR|O_CREAT);
    if(fd<0)
    {
        fprintf(stderr, "fopen %s failed, reason: %s. \nexit.\n",filename,strerror(errno));
        return -1;;
    }

    do{
        //sleep(1);
        if( (len = read(fd,buffer,BUF_SIZE)) < 0 )
        {
            fprintf(stderr, "read from %s failed, reason: %s. \nexit.\n", filename, strerror(errno));
			exit(-1);
        }

    }while( len > 0);

    close(fd);
    return 0;
}
