#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define BLOCK_SIZE  512      //每次分配内存块大小

#define TOTAL_SIZE (  1024 * 1024 ) //分配的总内存的大小

#define NUM   (TOTAL_SIZE/BLOCK_SIZE)

int main(int argc, char **argv)
{
        char *ptr[NUM];
        int i=0, k=0;

        for(k = 0; k< 1024 ; k++){
            for(i = 0; i < NUM ; i++)
            {
                ptr[i] = malloc(BLOCK_SIZE);
                if(!ptr[i]) fprintf(stderr,"malloc failed. reason:%s\n",strerror(errno));
                else{
                     ptr[i][0] = '\0';
                }
            }

            for(i = 0; i < NUM ; i++){
                if(ptr[i]) free(ptr[i]);
            }
        }

        return 0;
}
