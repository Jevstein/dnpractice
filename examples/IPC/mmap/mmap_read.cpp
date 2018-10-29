/*
 *  mmap_read.cpp 
 *  mmap_read
 *
 *  Created by Jevstein on 2018/10/29 11:55.
 *  Copyright @ 2018year Jevstein. All rights reserved.
 *
 *  参考: https://blog.csdn.net/hj605635529/article/details/73163513
 *
 *  共享内存/存储映射(mmap): 读
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>

struct STU
{
	int age;
	char name[20];
	char sex;
};

int main(int argc, char *argv[]) //这个进程读
{
	if (argc != 2)
	{
		printf("./a.out  file");
		exit(1);
	}

	int fd = open(argv[1], O_RDONLY, 0644);
	if (fd < 0)
	{
		perror("open");
		exit(2);
	}

	struct STU student;

	struct STU *p = (struct STU*)mmap(NULL, sizeof(struct STU), PROT_READ, MAP_SHARED, fd, 0);
	if (p == MAP_FAILED)
	{
		perror("mmap");
		exit(3);
	}
	close(fd);
	int i = 0;
	while (1)
	{
		printf("id = %d\tname = %s\t%c\n", p->age, p->name, p->sex);
		sleep(2);
	}
	int ret = munmap(p, sizeof(student));
	if (ret < 0)
	{
		perror("mmumap");
		exit(4);
	}

	return 0;
}

//compile:
// $ g++ -o ../../../bin/mmap_rd mmap_read.cpp