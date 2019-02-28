
#include <stdlib.h>  
#include <stdio.h>  
#include <errno.h>  
#include <unistd.h>  
#include <sys/types.h>  
#include <sys/socket.h>  
#include <netinet/in.h>  
#include <arpa/inet.h>
#include "prefixhead.h"

void echo_client(int sock)  
{  
    struct sockaddr_in addr;  
    memset(&addr, 0, sizeof(addr));  
    addr.sin_family = AF_INET;  
    addr.sin_port = htons(PEER_PORT);  
    addr.sin_addr.s_addr = inet_addr(PEER_IP);

	socklen_t addr_len = sizeof(addr);//此处若不赋值，首次recvfrom的ip地址总会为: 0.0.0.0
	
    char ip[64] = {0};
	char buf[BUF_SIZE] = {0};
	int ret = 0;

	do
	{
		//1.req: handshake1
		strcpy(buf, "Hello Alice, I am bob from udp_client!");
		ret = ::sendto(sock, buf, strlen(buf), 0, (struct sockaddr *)&addr, sizeof(addr));
		ECHO("req", "sendto", sock, buf, addr, ip, ret);

		//2.ack: handshake3
		ret = ::recvfrom(sock, buf, BUF_SIZE - 1, 0, (struct sockaddr *)&addr, &addr_len);
		ECHO("ack", "recvfrom", sock, buf, addr, ip, ret);

		//3.send
		strcpy(buf, "great!");
		ret = ::sendto(sock, buf, strlen(buf), 0, (struct sockaddr *)&addr, sizeof(addr));
		ECHO("send", "sendto", sock, buf, addr, ip, ret);

		//4.recv
		ret = ::recvfrom(sock, buf, BUF_SIZE - 1, 0, (struct sockaddr *)&addr, &addr_len);
		ECHO("recv", "recvfrom", sock, buf, addr, ip, ret);
	} while (0);
}  

int main(void)  
{  
    int sock;  
    if ((sock = ::socket(PF_INET, SOCK_DGRAM, 0)) < 0)  
        ERR_EXIT("socket");
    
    echo_client(sock);

    ::close(sock);
    
    return 0;
}