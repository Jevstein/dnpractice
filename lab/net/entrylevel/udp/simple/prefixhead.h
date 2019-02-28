/***************************************************************************** 
 *  @COPYRIGHT NOTICE 
 *  @Copyright (c) 2017, Microbeam software technology (Shanghai) co. LTD 
 *  @All rights reserved 
 
 *  @file     : PrefixHead.h 
 *  @version  : ver 1.0 
 
 *  @author   : yiwenqiang 
 *  @date     : 2019/1/7 17:33 
 *  @brief    : brief 
*****************************************************************************/ 

#ifndef _PREFIX_HEAD_H_
#define _PREFIX_HEAD_H_
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
#include <unistd.h>
#include <dlfcn.h>
#include <assert.h>
#include <string.h>
#include <errno.h>

#include <signal.h>
#include <netinet/in.h>
//#include <sys/timeb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>

// log
#define LOG_ERR(fmt,...) { time_t now = time(NULL); printf("[%.24s][error][srv] "fmt" ["__FILE__":%s().%d]\n", ctime(&now), ##__VA_ARGS__, __FUNCTION__, __LINE__); }
#define LOG_EXP(fmt,...) { time_t now = time(NULL); printf("[%.24s][exception][srv] "fmt" ["__FILE__":%s().%d]\n", ctime(&now), ##__VA_ARGS__, __FUNCTION__, __LINE__); }
#define LOG_WAR(fmt,...) { time_t now = time(NULL); printf("[%.24s][warning][srv] "fmt"\n", ctime(&now), ##__VA_ARGS__); }
#define LOG_INF(fmt,...) { time_t now = time(NULL); printf("[%.24s][inf][srv] "fmt"\n", ctime(&now), ##__VA_ARGS__); }
#define LOG_DBG(fmt,...) { time_t now = time(NULL); printf("[%.24s][dbg][srv] "fmt"\n", ctime(&now), ##__VA_ARGS__); }

#define ERR_EXIT(m) do { 	\
	perror(m); 				\
	exit(EXIT_FAILURE); 	\
} while(0)  

// echo
#define ECHO(flag, action, sock, buf, addr, ip, ret) do {							\
	if (ret < 0) {																	\
		LOG_ERR("failed to %s '%s'", flag, buf);									\
		ERR_EXIT(action "error");													\
	}																				\
    inet_ntop(AF_INET, &addr.sin_addr, ip, sizeof(ip));								\
	LOG_INF("[%s][%s:%d][%d]: '%s'", flag, ip, ntohs(addr.sin_port), sock, buf);	\
} while(0)

// ip and port
#define PEER_IP "127.0.0.1"
#define PEER_PORT 6666

#define BUF_SIZE 100

#endif //_PREFIX_HEAD_H_
