/*
 *  mmap_write.cpp 
 *  mmap_write
 *
 *  Created by Jevstein on 2018/10/29 11:57.
 *  Copyright @ 2018year Jevstein. All rights reserved.
 *
 *  参考: https://blog.csdn.net/hj605635529/article/details/73163513
 *
 *  共享内存/存储映射(mmap): 写
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <string.h>
 
struct STU
{
	int age;
	char name[20];
	char sex;
};
 
int main(int argc,char *argv[]) //这个进程用于创建映射区进行写。
{
	if(argc != 2)
	{
		printf("./a.out  file.\n");
		exit(1);
	}
 
	struct STU student = {10,"xiaoming",'m'};
 
	int fd = open(argv[1],O_RDWR|O_CREAT|O_TRUNC,0644);
	if(fd < 0)
	{
		perror("open");
		exit(2);
	}
	ftruncate(fd,sizeof(struct STU)); //文件拓展大小。
	
	struct STU *p = (struct STU*)mmap(NULL,sizeof(struct STU),PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);//创建一个结构体大小的共享映射区。共享映射区我们可以当做数组区看待。
	if(p == MAP_FAILED)
	{
		perror("mmap");
		exit(3);
	}
	close(fd); //关闭不用的文件描述符。
	while(1)
	{
		memcpy(p,&student,sizeof(student));
		student.age++;
		sleep(1);
	}
	int ret = munmap(p,sizeof(student));
	if(ret < 0)
	{
		perror("mmumap");
		exit(4);
	}
 
	return 0;
}

//compile:
// $ g++ -o ../../../bin/mmap_wr mmap_write.cpp