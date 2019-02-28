/*
 *  tcp_epoll_server.cpp 
 *  tcp_epoll_server
 *
 *  Created by Jevstein on 2018/11/1 17:04.
 *  Copyright @ 2018year Jevstein. All rights reserved.
 *
 */
#include "epoll_api.h"

typedef struct st_socket
{
	YI_SOCKET sockfd;
	int type;//0=����socket, 1=����socket
	char buf[256];

	st_socket(YI_SOCKET sockfd, int type){ this->sockfd = sockfd; this->type = type; }
}Tsocket, *PTsocket;

int onRecv(YI_SOCKET sockfd)
{
	char buf[256] = { 0 };
	int len = socket_recv(sockfd, buf, sizeof(buf));
	if (len <= 0)//ע���ж������Ƿ�Ͽ�
		return -1;

	LOG_INFO("recv[%d]>> %s", len, buf);

	if (strcmp(buf, "close") == 0)
		return -2;//�����˳�

	if (strcmp(buf, "exit") == 0)
		return -3;//�����˳�

	return 0;
}

void onSend(YI_SOCKET sockfd, char *buf, int len)
{
	len = socket_send(sockfd, buf, len);
	if (len < 0)
		return;

	LOG_INFO("send[%d]<< %s", len, buf);
}

bool start_epoll(YI_SOCKET listen_fd)
{
	YI_EPFD epfd_ = -1;
	net_io_event* ep_events_ = NULL;

	// 1.create epoll
	epfd_ = io_create(&ep_events_, 4096);
	if (epfd_ < 0)
		return false;

	// 2.set epoll: EPOLLIN 
	st_socket stlisten(listen_fd, 0);
	if (!io_add_fd(epfd_, listen_fd, EPOLLIN, &stlisten))
		return false;

	// 3.wait epoll
	bool loop = true;
	while (loop)
	{
		int idxs = io_wait(epfd_, &ep_events_, 2000);
		if (idxs < 0)
		{
			if (errno == EINTR)
				continue;

			LOG_ERR("failed to epoll_wait! err: %s", strerror(errno));
			break;
		}

		for (int i = 0; i < idxs; ++i)
		{
			st_socket* stsocket = (st_socket *)io_get_userdata(&ep_events_, i);
			if (NULL == stsocket)
			{
				LOG_ERR("failed to io_get_userdata! idxs=%d, i=%d", idxs, i);
				sleep(5);
				continue;
			}

			if (stsocket->type == 0)
			{//[listen]�����¼�: accept
				struct sockaddr_in6 clt_addr;
				YI_SOCKET conn_fd = socket_accept(stsocket->sockfd, &clt_addr);
				if (conn_fd < 0)
					continue;

				st_socket *stsock_conn = new st_socket(conn_fd, 1);
				if (!io_add_fd(epfd_, conn_fd, EPOLLIN/* | EPOLLET*/, stsock_conn))
					continue;
			}
			else
			{//[client]�����¼�: recv | send
				int events = io_get_event(&ep_events_, i);
				//LOG_ERR("ev=%d, i=%d", ev, i);

				if (events & EPOLLIN)
				{//recv
					int ret = onRecv(stsocket->sockfd);
					if (ret == -3)
					{//�˳�
						io_del_fd(epfd_, stsocket->sockfd, 0);
						socket_close(stsocket->sockfd);
						delete stsocket;
						loop = false;
						break;
					}
					else if (ret == -2 || ret == -1)
					{//�ر�
						io_del_fd(epfd_, stsocket->sockfd, 0);
						socket_close(stsocket->sockfd);
						delete stsocket;
						break;
					}

					// pre-send
					strcpy(stsocket->buf, "hi~, client");
					io_modify_fd(epfd_, stsocket->sockfd, EPOLLIN | EPOLLOUT/* | EPOLLET*/, stsocket);
				}
				else if (events & EPOLLOUT)
				{//send
					if (stsocket->buf[0] == '\0')
					{//����������
						io_modify_fd(epfd_, stsocket->sockfd, EPOLLIN/* | EPOLLET*/, stsocket);
					}
					else
					{//����������
						onSend(stsocket->sockfd, stsocket->buf, strlen(stsocket->buf));
						stsocket->buf[0] = '\0';
					}
				}
				else if (events & EPOLLERR || events & EPOLLRDHUP)
				{//error | hup
					LOG_ERR("failed to get event(EPOLLERR|EPOLLRDHUP): %d, err: %s", events, strerror(errno));
					////if(errno == 0)
					////	connection->OnDisConnect();
					//connection->OnSend();
				}
				else
				{//unknown
					LOG_ERR("get unknown event: %d, err: %s", events, strerror(errno));
				}
			}
		}
	}

	io_close(epfd_, ep_events_);

	return true;
}

bool start_server(const char *ip, int port)
{
	struct addrinfo* addrinfo_res_listen = NULL;

	// 1.create socket
	YI_SOCKET listen_fd_ = socket_create(ip, port, SOCK_STREAM, &addrinfo_res_listen);
	if (listen_fd_ < 0)
		return false;

	// *.set reuse
	if (!set_reuse_port(listen_fd_))
	{
		addrinfo_res_listen = addrinfo_res_listen->ai_next;
		return false;
	}

	// 2.bind: �����󶨣��޷�LISTEN״̬���޷�����"��������"���ͻ���connect��ץ������ Flags [R.]
	if (!socket_bind(listen_fd_, addrinfo_res_listen))
	{
		addrinfo_res_listen = addrinfo_res_listen->ai_next;
		return false;
	}

	// 3. listen: ����LISTEN״̬�����ͻ���connect��"��������"���ѽ���
	if (!socket_listen(listen_fd_, 128))
	{
		addrinfo_res_listen = addrinfo_res_listen->ai_next;
		return false;
	}

	// *.start epoll
	if (!start_epoll(listen_fd_))
	{
		addrinfo_res_listen = addrinfo_res_listen->ai_next;
		return false;
	}

	socket_close(listen_fd_);

	return true;
}

int main(int argc, char *argv[])
{
	LOG_INFO("--------- simple TCP server start ---------");
	printf("usage: file_lock [ 0.0.0.0 | 8888 ]\n");

	const char *ip = "0.0.0.0";
	int port = 8888;

	if (argc == 3)
	{
		ip = argv[1];
		port = atoi(argv[2]);
	}

	start_server(ip, port);

	//while (1) sleep(1);

	LOG_INFO("--------- the end ---------");

	return 0;
}

//complile:
// $ g++ -g -o ../../../../../bin/tcp_epoll_server ../socket_api.cpp epoll_api.cpp tcp_epoll_server.cpp
// 
//package capture:
// $ sudo tcpdump -iany tcp port 8888
// $ netstat -nat -p |grep 8888