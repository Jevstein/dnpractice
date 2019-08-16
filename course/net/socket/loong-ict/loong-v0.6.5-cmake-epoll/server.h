#ifndef LOONG_SERVER_H
#define LOONG_SERVER_H

#include <unistd.h>

void daemonize();
pid_t server_singleton();


#endif //LOONG_SERVER_H
