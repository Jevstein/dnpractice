
#ifndef _HEADER_H_
#define _HEADER_H_
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>

// log
#define LOG_ERR(fmt,...) { time_t now = time(NULL); printf("[%.24s][error][srv] "fmt" ["__FILE__":%s().%d]\n", ctime(&now), ##__VA_ARGS__, __FUNCTION__, __LINE__); }
#define LOG_EXP(fmt,...) { time_t now = time(NULL); printf("[%.24s][exception][srv] "fmt" ["__FILE__":%s().%d]\n", ctime(&now), ##__VA_ARGS__, __FUNCTION__, __LINE__); }
#define LOG_WAR(fmt,...) { time_t now = time(NULL); printf("[%.24s][warning][srv] "fmt"\n", ctime(&now), ##__VA_ARGS__); }
#define LOG_INF(fmt,...) { time_t now = time(NULL); printf("[%.24s][inf][srv] "fmt"\n", ctime(&now), ##__VA_ARGS__); }
#define LOG_DBG(fmt,...) { time_t now = time(NULL); printf("[%.24s][dbg][srv] "fmt"\n", ctime(&now), ##__VA_ARGS__); }

#endif//_HEADER_H_