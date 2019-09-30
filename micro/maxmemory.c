/*
*  测试malloc最大内存申请数量
*/
#include <stdio.h>
#include <stdlib.h>

unsigned int maximum = 0;

int main(int argc, char *argv[])
{
    unsigned int blocksize[] = {1024 * 1024, 1024, 1};
    const int count = sizeof(blocksize)/sizeof(unsigned int);
    int i, k;
    for (i = 0; i < count; i++)
    {
        for (k = 1; ; i++)
        {
            void *block = malloc(maximum + blocksize[i] * k);
            if (!block)
                break;
            
            maximum += blocksize[i] * k;
            free(block);
        }
    }
    
    printf("the maximum amount of memory using malloc is %u bytes!\n", maximum);
    return 0;
}