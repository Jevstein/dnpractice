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
#define TO_YES 0	//UDP客户端除了采用recvfrom/sendto，还可以在connect后采用recv/send
#define SERV_PORT 8080

int main(int argc, char *argv[])
{
    struct addrinfo hint, *result;
    int res, sfd, len;
	char buf[BUF_SIZE];
	unsigned short port = SERV_PORT;

	// ip-port address
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(struct sockaddr_in));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
	//addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_addr.s_addr = inet_addr("192.168.246.128");

	// 1.create udp socket
	sfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sfd == -1) 
    {
        perror("error: socket error!\n");
        exit(1);
    }

	//2.connect
#if !TO_YES
	if (connect(sfd, (struct sockaddr *)&addr, sizeof(struct sockaddr_in)) != 0)
	{
		printf("error: failed to connect! err: %s\n", strerror(errno));
		exit(1);
	}

	printf("0.connect success!\n");
#endif

	//3.send/sendto 
    snprintf(buf, BUF_SIZE, "Hi~ server. Now I will send data to you.");
#if TO_YES
	res = sendto(sfd, buf, strlen(buf), 0, (struct sockaddr*)&addr, strlen(buf));
#else
	res = send(sfd, buf, strlen(buf), 0);
#endif
	if (res <= 0)
    {
		printf("error: failed to send! err: %s\n", strerror(errno));
		exit(1);
    }
    printf("1.send[%d]: %s\n", res, buf);

	//4.recv/recvfrom
	memset(buf, 0, sizeof(buf));
#if TO_YES
	res = recvfrom(sfd, buf, sizeof(buf), 0, (struct sockaddr *)&addr, (socklen_t *)&len);
#else
	res = recv(sfd, buf, BUF_SIZE, 0);
#endif
	if (res <= 0)
	{
		printf("error: failed to recv! err: %s\n", strerror(errno));
		exit(1);
	}

	printf("2.recv[%d]: %s\n\n", res, buf);
    
    return 0;
}

//compile:
// $ gcc -o ../../../bin/c_udp_simple_client udpclient_v1.c