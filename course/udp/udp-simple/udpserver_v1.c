#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>


#define BUF_SIZE 1024
#define TO_YES 1		//UDP服务端必须采用recvfrom/sendto
#define SERV_PORT 8080

int main(int argc, char *argv[])
{
    struct addrinfo hint, *result;
    struct sockaddr_in addr_clt;
    int res, sfd, len_clt;
	char buf[BUF_SIZE] = {0};
	unsigned short port = SERV_PORT;
    
    struct sockaddr_in addr;

	// ip-port address
	memset(&addr, 0, sizeof(struct sockaddr_in));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);;
	/* INADDR_ANY表示不管是哪个网卡接收到数据，只要目的端口是SERV_PORT，就会被该应用程序接收到 */
	addr.sin_addr.s_addr = htonl(INADDR_ANY);  //自动获取IP地址
	//addr.sin_addr.s_addr = inet_addr("192.168.246.128");//[注意]: 即使绑定了地址，send依然报错err: Destination address required 

	// 1.create socket
    sfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sfd == -1) 
    {
		//perror("error: failed to create socket!\n");
		printf("error: failed to create socket! err: %s\n", strerror(errno));
        exit(1);
    }

	// 2.bind socket & ip-port address
    res = bind(sfd, (struct sockaddr *)&addr, sizeof(struct sockaddr_in));
    if (res == -1) 
    {
		printf("error: failed to bind! err: %s\n", strerror(errno));
        exit(1);
    }

	// 3.recv/recvform and send/sendto
    while (1) 
    {
        printf("1.waiting for client ...\n");

		//3.1.recv/recvform
#if TO_YES
		res = recvfrom(sfd, buf, sizeof(buf), 0, (struct sockaddr *)&addr_clt, (socklen_t *)&len_clt);
#else
		res = recv(sfd, buf, BUF_SIZE, 0);
#endif
        if (res == -1) 
		{
			printf("error: failed to recvfrom! err: %s\n", strerror(errno));
            exit(1);
        }
        printf("2.recv[%d]: %s\n", res, buf);
           
		//3.2.send/sendto
        snprintf(buf, BUF_SIZE, "Hi~ client. I reveived [%d] success.", res);
#if TO_YES
		res = sendto(sfd, buf, strlen(buf), 0, (struct sockaddr*)&addr_clt, len_clt);
#else
		//以下无效，报错err: Destination address required
		res = send(sfd, buf, strlen(buf), 0);
#endif
		if (res != strlen(buf))
		{
			printf("error: failed to send! err: %s\n", strerror(errno));
            exit(1);
        }

		printf("3.send[%d]: %s\n\n", res, buf);
    }
}

//compile:
// $ gcc -o ../../../bin/c_udp_simple_server udpserver_v1.c
// 
//package capture:
// $ sudo tcpdump -iany tcp port 8080
// $ netstat -nat -p |grep 8080