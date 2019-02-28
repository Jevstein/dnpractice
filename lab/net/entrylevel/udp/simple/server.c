#include <stdio.h>  
#include <stdlib.h>  
#include <unistd.h>  
#include <errno.h>  
#include <sys/types.h>  
#include <sys/socket.h>  
#include <netinet/in.h>  
#include <string.h>  
#include "prefixhead.h"

void echo_server(int sock)  
{  
    struct sockaddr_in addr;
	socklen_t addr_len = sizeof(addr);//此处若不赋值，首次recvfrom的ip地址总会为: 0.0.0.0
    
    char ip[64] = {0};
	char buf[BUF_SIZE] = {0};
	int ret = 0;

    while (1)
    {
        memset(buf, 0, sizeof(buf));
        ret = ::recvfrom(sock, buf, sizeof(buf), 0,  (struct sockaddr *)&addr, &addr_len);
		ECHO("recv", "recvfrom", sock, buf, addr, ip, ret);

		ret = ::sendto(sock, buf, strlen(buf), 0, (struct sockaddr *)&addr, sizeof(addr));
		ECHO("echo", "sendto", sock, buf, addr, ip, ret);
    }
}

int main(void)  
{  
    int sock;  
    if ((sock = ::socket(PF_INET, SOCK_DGRAM, 0)) < 0)  
        ERR_EXIT("socket error");  
    
    struct sockaddr_in servaddr;  
    memset(&servaddr, 0, sizeof(servaddr));  
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PEER_PORT); 
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);  
    
    LOG_INF("[bind]: port=%d", PEER_PORT);  
    if (::bind(sock, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)  
        ERR_EXIT("bind error");  
    
    echo_server(sock);

    ::close(sock);
    
    return 0;  
}