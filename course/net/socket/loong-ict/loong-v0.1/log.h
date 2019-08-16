#ifndef LOONG_LOG_H
#define LOONG_LOG_H

#include <string>
#include <cstring>

#define HANDLE(X) \
    do { \
        if ((X) == -1) { \
            log("[Error]", strerror(errno)); \
            exit(1); \
        } \
    } while(0)

void log(const std::string &log_head, const std::string &log_body);


#endif //LOONG_LOG_H
