#include <fstream>
#include <ctime>
#include "log.h"

void log(const std::string &log_head, const std::string &log_body) {
    static std::ofstream log_fs;
    if (!log_fs.is_open()) {
        log_fs.open("log.txt", std::ofstream::out | std::ofstream::app);
    }
    time_t t;
    time(&t);
    char time_string[32];
    strftime(time_string, sizeof(time_string), "%Y-%m-%d %H:%M:%S", localtime(&t));
    log_fs << "[" << time_string << "] " << log_head << " " << log_body << std::endl;
}
