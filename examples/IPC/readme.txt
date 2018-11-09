
IPC(Interprosses communication): 进程间通信

通信方式：
1.管道(pipe): 匿名管道、命名管道、半双工/双工
2.共享文件(fifo):
3.共享内存(shm/mmap)：
  1).shm：shm_xx函数组(shm_get,shm_at,shm_dt,shm_ctl)，system V标准
  2).mmap：存储映射I/O，POSIX标准
  [区别]: 参考 https://blog.csdn.net/hj605635529/article/details/73163513 
	1、mmap是在磁盘上建立一个文件，每个进程地址空间中开辟出一块空间进行映射。
	   而对于shm而言，shm每个进程最终会映射到同一块物理内存。shm保存在物理内存，
	   这样读写的速度要比磁盘要快，但是存储量不是特别大。
	2、相对于shm来说，mmap更加简单，调用更加方便，所以这也是大家都喜欢用的原因。
	3、另外mmap有一个好处是当机器重启，因为mmap把文件保存在磁盘上，这个文件还保
	  存了操作系统同步的映像，所以mmap不会丢失，但是shmget就会丢失。
4.信号量(sem): PV操作.
  注：进程间也可以使用互斥锁(mutex)来达到同步的目的,但应在pthread_mutex_init初始化之前,修改其属性为进程间共享,如:
  { https://blog.csdn.net/qq_35396127/article/details/78942245 
		// 建立映射区
		mm = mmap(NULL,sizeof(*mm),PROT_READ|PROT_WRITE,MAP_SHARED|MAP_ANON,-1,0);
		memset(mm,0x00,sizeof(*mm));

		pthread_mutexattr_init(&mm->mutexattr); // 初始化 mutex 属性
		pthread_mutexattr_setpshared(&mm->mutexattr, PTHREAD_PROCESS_SHARED);// 修改属性为进程间共享
		pthread_mutex_init(&mm->mutex,&mm->mutexattr);// 初始化一把 mutex 锁
    
		pid = fork();
  }
5.信号(signal)：
6.套接字(socket):