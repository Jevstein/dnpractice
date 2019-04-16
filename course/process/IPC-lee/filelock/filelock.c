/*
 *  filelock.c 
 *  filelock
 *
 *  Created by Jevstein on 2018/10/30 9:24.
 *  Copyright @ 2018year Jevstein. All rights reserved.
 *
 *  [概念]:
 *     文件锁
 *     1.建议性锁：lockf()、fcntl(), [内核和系统都不适用建议性锁，采用强制性锁的影响很大，每次读写操作都必须检查是否有所存在]
 *     2.强制性锁：fcntl()
 *     3.记录锁：文件的同一部分不能同时建立读取锁和写入锁
 *        1).读取锁（共享锁）
 *        2).写入锁（排斥锁)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "lock_set.h"

#define WR_NAME "FILE_LOCK_WR"
#define RD_NAME "FILE_LOCK_RD"

// 写入锁
int file_lock_wr()
{
	int fd = open(WR_NAME, O_RDWR | O_CREAT, 0644);
	if (fd < 0)
	{
		printf("Open file error!\n");
		return -1;
	}
	//给文件上写入锁
	lock_set(fd, F_WRLCK);
	{
		getchar();
	}
	//给文件解锁
	lock_set(fd, F_UNLCK);
	getchar();
	close(fd);

	return 0;
}

// 读取锁
int file_lock_rd()
{
	int fd = open(RD_NAME, O_RDWR | O_CREAT, 0644);
	if (fd < 0)
	{
		printf("Open file error!\n");
		return -1;
	}
	//给文件上读取锁
	lock_set(fd, F_RDLCK);
	getchar();
	//给文件解锁
	lock_set(fd, F_UNLCK);
	getchar();
	close(fd);

	return 0;
}

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		printf("usage: file_lock [ -wr | -rd ]\n");
		return -1;
	}

	if (strcmp(argv[1], "-wr") == 0)
	{
		printf("---------- write lock test ---------\n\n");
		file_lock_wr();
	}
	else if (strcmp(argv[1], "-rd") == 0)
	{
		printf("---------- read lock test ---------\n\n");
		file_lock_rd();
	}
	else
	{
		printf("usage: file_lock [ -wr | -rd ]\n");
		return -1;
	}


	printf("---------- the end ---------\n");

	return 0;
}


//compile:
// $ gcc -o ../../../bin/file_lock filelock.c