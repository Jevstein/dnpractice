/*
 *  epoll_api.h 
 *  epoll_api
 *
 *  Created by Jevstein on 2018/11/1 17:06.
 *  Copyright @ 2018year Jevstein. All rights reserved.
 *
 *  核心函数:
 *  1.int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);
 *    op:     EPOLL_CTL_ADD、EPOLL_CTL_MOD、EPOLL_CTL_DEL
 *    events：EPOLLIN、EPOLLOUT、EPOLLRDHUP、EPOLLPRI、EPOLLERR、EPOLLHUP、EPOLLET、EPOLLONESHOT、EPOLLWAKEUP
 */

#ifndef __EPOLL_API_H__
#define __EPOLL_API_H__

#include <sys/epoll.h>
#include "../socket_api.h"

//#ifndef LOG_INFO
//	//#define LOG_INFO(fmt,...) printf(fmt"\n", ##__VA_ARGS__)
//	//#define LOG_ERR(fmt,...) printf("[error] "fmt"\n", ##__VA_ARGS__)
//	#define LOG_INFO(fmt,...) { time_t now = time(NULL); printf("[%.24s] "fmt"\n", ctime(&now), ##__VA_ARGS__); }
//	#define LOG_ERR(fmt,...) { time_t now = time(NULL); printf("[%.24s][error] "fmt"\n", ctime(&now), ##__VA_ARGS__); }
//#endif

//// event定义
//#if defined(YI_OS_MAC) || defined(YI_OS_WIN32) //mac: kqueue, win: select|iocp
//#	define EPOLLIN			(1 << 0)	//#define EVFILT_READ	(-1)    //表示对应的文件描述符可以读（包括对端SOCKET正常关闭）
//#	define EPOLLOUT			(1 << 1)	//#define EVFILT_WRITE	(-2)    //表示对应的文件描述符可以写
//#	define EPOLLPRI			(1 << 2)	//#define EVFILT_AIO	(-3)	/* attached to aio requests */ //表示对应的文件描述符有紧急的数据可读（这里应该表示有带外数据到来）
//#	define EPOLLERR			(1 << 3)	//#define EVFILT_VNODE	(-4)	/* attached to vnodes */       //表示对应的文件描述符发生错误
//#	define EPOLLHUP			(1 << 4)	//#define EVFILT_PROC	(-5)	/* attached to struct proc */  //表示对应的文件描述符被挂断
//#	define EPOLLET			(1 << 5)	//#define EVFILT_SIGNAL	(-6)	/* attached to struct proc */  //将EPOLL设为边缘触发(Edge Triggered)模式，这是相对于水平触发(Level Triggered)来说的
//#	define EPOLLONESHOT		(1 << 6)	//#define EVFILT_TIMER	(-7)	/* timers */                   //只监听一次事件，当监听完这次事件之后，如果还需要继续监听这个socket的话，需要再次把这个socket加入到EPOLL队列里
////#	define EPOLLMACHPORT	(1 << 7)	//#define EVFILT_MACHPORT (-8)	/* Mach portsets */
////#	define EPOLLFS			(1 << 8)	//#define EVFILT_FS		(-9)	/* Filesystem events */
////#	define EPOLLUSER		(1 << 9)	//#define EVFILT_USER   (-10)   /* User events */
////										/* (-11) unused */
////#	define EPOLL_EV			(1 << 10)	//#define EV
//#else//linux: epoll
//#	include <sys/epoll.h>
//#	include <sys/wait.h>
//#endif

typedef int YI_EPFD;
typedef void net_io_event;
typedef net_io_event* net_io_event_p;

YI_EPFD io_create(net_io_event** events, int nfds = 4096);
bool io_add_fd(YI_EPFD epfd, YI_SOCKET sockfd, int events, void* key);
bool io_modify_fd(YI_EPFD epfd, YI_SOCKET sockfd, int events, void* key);
bool io_del_fd(YI_EPFD epfd, YI_SOCKET sockfd, int events = 0);
int io_wait(YI_EPFD epfd, net_io_event** events, int maxevents = 2000);
void io_close(YI_EPFD epfd, net_io_event* events);

int io_get_event(net_io_event** events, int idx);
void* io_get_userdata(net_io_event** events, int idx);


#endif //__EPOLL_API_H__