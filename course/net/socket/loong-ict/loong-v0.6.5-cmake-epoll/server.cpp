#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/file.h>
#include <sys/stat.h>
#include "log.h"

void daemonize() {
    pid_t pid;
    int fd;
    if ((pid = fork()) < 0) {
        std::cerr << "[Error] Can't fork!" << std::endl;
    } else if (pid != 0) {
        exit(0);
    }
    setsid();
    umask(0077);
    if ((fd = open("/dev/null", O_RDWR)) != -1) {
        dup2(fd, STDIN_FILENO);
        dup2(fd, STDOUT_FILENO);
        dup2(fd, STDERR_FILENO);
        if (fd > STDERR_FILENO) {
            close(fd);
        }
    }
}

pid_t server_singleton() {
    int pid_file_fd;
    HANDLE(pid_file_fd = open("loong.pid", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR));
    int lock = flock(pid_file_fd, LOCK_EX | LOCK_NB);
    if (lock == -1 && errno == EWOULDBLOCK) {
        char pid_string[32];
        memset(pid_string, 0, sizeof(pid_string));
        HANDLE(read(pid_file_fd, pid_string, sizeof(pid_string)));
        close(pid_file_fd);
        auto pid = strtol(pid_string, nullptr, 10);
        log("[Info]", "Detect server pid=" + std::string(pid_string));
        return pid;
    } else {
        std::basic_string<char> pid_string = std::to_string(getpid());
        HANDLE(ftruncate(pid_file_fd, 0));
        HANDLE(write(pid_file_fd, pid_string.c_str(), pid_string.size()));
        log("[Info]", "Set server pid=" + pid_string);
        return -1;
    }
}
