
IPC(Interprosses communication): 进程间通信

通信方式：
1.管道(pipe): 匿名管道、命名管道、半双工/双工
2.共享文件(fifo):
3.共享内存(shm/mmap)：
  1).shm：shm_xx函数组(shm_get,shm_at,shm_dt,shm_ctl)，system V标准
  2).mmap：存储映射I/O，POSIX标准
4.信号量(sem): PV操作,注：mutex不能用于进程间加锁
5.信号(signal)：
6.套接字(socket):