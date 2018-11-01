/*
 *  epoll_api.cpp 
 *  epoll_api
 *
 *  Created by Jevstein on 2018/11/1 17:06.
 *  Copyright @ 2018year Jevstein. All rights reserved.
 *
 */
#include "epoll_api.h"

int epoll_ctl_fd(YI_EPFD epfd, int op, int fd, int events, void* key)
{
	struct epoll_event plevt;
	plevt.events = events;
	plevt.data.ptr = key;

	return epoll_ctl(epfd, op, fd, &plevt);
}

YI_EPFD io_create(net_io_event** events, int max_nfds /*= 4096*/)
{
	YI_EPFD epfd = epoll_create(max_nfds);
	if (epfd < 0)
	{
		LOG_ERR("failed to epoll_create! fd: %d, err: %s", epfd, strerror(errno));
		return -1;
	}

	*events = new epoll_event[nfds];
	if (NULL == *events)
	{
		LOG_ERR("failed to new epoll_event!");
		return -2;
	}

	return epfd;
}

int io_add_fd(YI_EPFD epfd, int fd, int events, void* key)
{
	return epoll_ctl_fd(epfd, EPOLL_CTL_ADD, fd, events, NULL);
}

int io_modify_fd(YI_EPFD epfd, int fd, int events, void* key)
{
	return epoll_ctl_fd(epfd, EPOLL_CTL_MOD, fd, events, NULL);
}

int io_del_fd(YI_EPFD epfd, int fd, int events /*= 0*/)
{
	return epoll_ctl_fd(epfd, EPOLL_CTL_DEL, fd, events, NULL);
}

int io_wait(YI_EPFD epfd, net_io_event* events, int max_nfds/* = 4096*/)
{
	return epoll_wait(epfd, events, max_nfds, 200);
}

void io_close(YI_EPFD epfd, net_io_event* events)
{
	::close(epfd);
	delete[] events;
}
