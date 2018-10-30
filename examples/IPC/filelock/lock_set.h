/*
 *  lockset.c 
 *  lockset
 *
 *  Created by Jevstein on 2018/10/30 11:03.
 *  Copyright @ 2018year Jevstein. All rights reserved.
 *
 *  [概念]:
 *     文件锁
 *     1.建议性锁：lockf()、fcntl(), [内核和系统都不适用建议性锁，采用强制性锁的影响很大，每次读写操作都必须检查是否有所存在]
 *     2.强制性锁：fcntl()
 *     3.记录锁：文件的同一部分不能同时建立读取锁和写入锁
 *        1).读取锁（共享锁）
 *        2).写入锁（排斥锁)
 *  [核心实现]:
 *      #include <unistd.h>
 *      #include <fcntl.h>
 *      int fcntl(int fd, int cmd, ... arg );
 *      参数1：
 *      参数2：
 *         F_SETLK(struct flock *);//设置文件锁 ( trylock )
 *         F_SETLKW(struct flock*);//设置文件锁（ lock ） W --- wait 
 *         F_GETLK(struct flock*);//获取文件锁
 *      参数3：
 *         struct flock {
 *             ...
 *             short l_type;  // Type of lock: F_RDLCK,F_WRLCK, F_UNLCK
 *             short l_whence;// How to interpret l_start: SEEK_SET, SEEK_CUR, SEEK_END
 *             off_t l_start; // Starting offset for lock
 *             off_t l_len;   // Number of bytes to lock
 *             pid_t l_pid;   // PID of process blocking our lock (F_GETLK only)
 *             ...
 *         };
 */

#include <unistd.h>
#include <fcntl.h>

int lock_set(int fd, int type)
{
	struct flock old_lock, lock;
	lock.l_whence = SEEK_SET;
	lock.l_start = 0;
	lock.l_len = 0; //0 表示对整个文件加锁
	lock.l_type = type;
	lock.l_pid = - 1;

	//判断文件是否上锁
	fcntl(fd, F_GETLK, &lock);
	if (lock.l_type != F_UNLCK)
	{//判断文件不能上锁的原因
		switch (lock.l_type)
		{
		case F_RDLCK: printf("Read lock already set by %d .\n", lock.l_pid); break;	//该文件已有读取锁
		case F_WRLCK: printf("Write lock already set by %d .\n", lock.l_pid); break;//该文件已有写入锁
		default:
			break;
		}
	}
	//l_type 可能已被F_FETLK修改过
	lock.l_type = type;

	//根据不同的type值进行阻塞式上锁或解锁
	if ((fcntl(fd, F_SETLKW, &lock)) < 0)
	{
		printf("Lock failed:type = %d\n", lock.l_type);
		return 1;
	}

	switch (lock.l_type)
	{
	case F_RDLCK: printf("Read lock set by %d {\n", getpid());	break;
	case F_WRLCK: printf("Write lock set by %d {\n", getpid());	break;
	case F_UNLCK: printf("} Release lock by %d \n\n", getpid());	return 1;
	default:
		break;
	}
	return 0;
}
