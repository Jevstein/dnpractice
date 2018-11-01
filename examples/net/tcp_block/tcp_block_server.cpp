/*
 *  simpletcp_server.cpp 
 *  simpletcp_server
 *
 *  Created by Jevstein on 2018/11/1 10:38.
 *  Copyright @ 2018year Jevstein. All rights reserved.
 *
 */
#include "../socket_api.h"

bool start_server(const char *ip, int port)
{
	struct addrinfo* addrinfo_res_listen;

	// 1.create socket
	YI_SOCKET listen_fd = socket_create(ip, port, SOCK_STREAM, &addrinfo_res_listen);
	if (listen_fd < 0)
		return false;

	// *.set reuse
	if (!set_reuse_port(listen_fd))
	{
		addrinfo_res_listen = addrinfo_res_listen->ai_next;
		return false;
	}

	// 2.bind: 若不绑定，无法LISTEN状态且无法进行"三次握手"，客户端connect后抓包返回 Flags [R.]
	if (!socket_bind(listen_fd, addrinfo_res_listen))
	{
		addrinfo_res_listen = addrinfo_res_listen->ai_next;
		return false;
	}

	// 3. listen: 进入LISTEN状态，若客户端connect后"三次握手"便已建立
	if (!socket_listen(listen_fd, 128))
	{
		addrinfo_res_listen = addrinfo_res_listen->ai_next;
		return false;
	}

	// 4.accept：去内核队列里取建立完成（三次握手established）的连接
	while (true)
	{
		struct sockaddr_in6 clt_addr;
		YI_SOCKET conn_fd = socket_accept(listen_fd, &clt_addr);
		if (conn_fd < 0)
		{
			continue;
		}

		//5.send & recv
		do 
		{
			//5.1.send: 
			char buf[256];
			snprintf(buf, sizeof(buf), "%s", "hi~, client");
			int len = socket_send(conn_fd, buf, strlen(buf));
			if (len < 0)
				break;
			LOG_INFO("send<< %s", buf);

			//5.2.recv
			memset(buf, 0, sizeof(buf));
			len = socket_recv(conn_fd, buf, sizeof(buf));
			if (len < 0)
				break;
			LOG_INFO("recv>> %s", buf);
		} while (0);

		socket_close(conn_fd);
	}

	socket_close(listen_fd);

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
// $ g++ -o ../../../bin/tcp_block_server ../socket_api.cpp tcp_block_server.cpp
// 
//package capture:
// $ sudo tcpdump -iany tcp port 8888
// $ netstat -nat -p |grep 8888