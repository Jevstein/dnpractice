/*
 *  tcp_epoll_client.cpp 
 *  tcp_epoll_client
 *
 *  Created by Jevstein on 2018/11/1 17:04.
 *  Copyright @ 2018year Jevstein. All rights reserved.
 *
 */

#include "../socket_api.h"


bool start_client()
{
	struct addrinfo* addrinfo_res_conn;

	// 1.create socket
	YI_SOCKET conn_fd = socket_create("127.0.0.1", 8888, SOCK_STREAM, &addrinfo_res_conn);
	if (conn_fd < 0)
		return false;

	// 2.connect
	if (!socket_connect(conn_fd, addrinfo_res_conn))
	{
		addrinfo_res_conn = addrinfo_res_conn->ai_next;
		return false;
	}

	//3.recv & send
	do
	{
		//3.1.recv
		char buf[256] = { 0 };
		int len = socket_recv(conn_fd, buf, sizeof(buf));
		if (len < 0)
			break;
		LOG_INFO("recv>> %s", buf);

		//3.2.send: 
		snprintf(buf, sizeof(buf), "%s", "hi~, server");
		len = socket_send(conn_fd, buf, strlen(buf));
		if (len < 0)
			break;
		LOG_INFO("send<< %s", buf);

	} while (0);

	//4.close
	socket_close(conn_fd);

	return true;
}

int main(int argc, char *argv[])
{
	LOG_INFO("--------- simple TCP client start ---------");

	start_client();

	LOG_INFO("--------- the end ---------");
	return 0;
}

//complile:
// $ g++ -o ../../../bin/tcp_block_client ../socket_api.cpp tcp_block_client.cpp
// 
//package capture:
// $ sudo tcpdump -iany tcp port 8888
// $ netstat -nat -p |grep 8888