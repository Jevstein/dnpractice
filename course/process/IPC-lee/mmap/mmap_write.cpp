/*
 *  mmap_write.cpp 
 *  mmap_write
 *
 *  Created by Jevstein on 2018/10/29 11:57.
 *  Copyright @ 2018year Jevstein. All rights reserved.
 *
 *  1.参考: https://blog.csdn.net/hj605635529/article/details/73163513
 *
 *  2.共享内存/存储映射(mmap): 写
 *
 *  3.mmap映射区和shm共享内存的区别，参考: https://blog.csdn.net/hj605635529/article/details/73163513
 *     先说一下普通的读写文件的原理，进程调用read或是write后会陷入内核，因为这两个
 *   函数都是系统调用，进入系统调用后，内核开始读写文件。假设内核在读取文件，内核
 *   首先把文件读入自己的内核空间，读完之后进程在内核态回归用户态，内核把读入内核内
 *   存的数据再copy进入进程的用户态内存空间。实际上我们同一份文件内容相当于读了两次，
 *   先读入内核空间，再从内核空间读入用户空间。
 *      Linux提供了内存映射函数mmap, 它把文件内容映射到一段内存上(准确说是虚拟内存上), 
 *   通过对这段内存的读取和修改, 实现对文件的读取和修改,mmap()系统调用使得进程之间可以
 *   通过映射一个普通的文件实现共享内存。普通文件映射到进程地址空间后，进程可以向访问
 *   内存的方式对文件进行访问，不需要其他系统调用(read,write)去操作
 *  4.过程调用：
 *      @brief			网络数据发送前打包
 *      @param addr		某个特定的地址作为起始地址，当被设置为NULL，系统会在地址空间选择一块合适的内存区域
 *      @param length	内存段的长度
 *      @param prot		用来设定内存段的访问权限，其中:
 *						PROT_READ	内存段可读
 *						PROT_WRITE	内存段可写
 *						PROT_EXEC	内存段可执行
 *						PROT_NONE	内存段不能被访问
 *      @param flags	参数控制内存段内容被修改以后程序的行为, 其中：
 *                      MAP_SHARED		进程间共享内存，对该内存段修改反映到映射文件中。提供了POSIX共享内存
 *						MAP_PRIVATE		内存段为调用进程所私有。对该内存段的修改不会反映到映射文件
 *						MAP_ANNOYMOUS	这段内存不是从文件映射而来的。内容被初始化为全0
 *						MAP_FIXED		内存段必须位于start参数指定的地址处，start必须是页大小的整数倍（4K整数倍）
 *						MAP_HUGETLB		按照大内存页面来分配内存空间
 *      @param			fd参数是用来被映射文件对应的文件描述符。通过open系统调用得到
 *      @param			offset设定从何处进行映射。
 *      @ret 成功返回指向内存区域的指针(即进程的地址空间的开始地址就是mmap函数的返回值)，失败返回MAP_FAILED
 *      void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);
 *    
 *  5.注意事项：
 *		1).映射区建立过程中隐含一次读操作
 *		2).MAP_SHARED时映射区权限 <= 打开文件权限
 *		3).映射区建立成功，文件即可关闭
 *		4).大小为0的文件无法创建映射区
 *		5).munmap参数应与mmap返回值严格对应
 *		6).偏移位置必须为4k的整数倍
 *		7).mmap返回值的判断不能省略
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