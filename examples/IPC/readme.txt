
IPC(Interprosses communication): 进程间通信

通信方式：
1.管道(pipe): 匿名管道、命名管道、半双工/双工
2.共享文件(fifo):
3.共享内存(shm/mmap)：
  1).shm：shm_xx函数组(shm_get,shm_at,shm_dt,shm_ctl)，system V标准
  2).mmap：存储映射I/O，POSIX标准
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