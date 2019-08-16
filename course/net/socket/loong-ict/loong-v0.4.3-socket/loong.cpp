#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <signal.h>
#include <time.h>

#define SOCKET_HANDLE(X) \
    do { \
        if ((X) == -1) { \
            log("[Error]", strerror(errno)); \
            exit(1); \
        } \
    } while(0)

std::ofstream log_fs;
struct sockaddr_in server_addr, client_addr;
socklen_t server_addr_len, client_addr_len;
int server_fd, client_fd;

void log(std::string log_head, std::string log_body) {
    time_t t;
    time(&t);
    char time_string[32];
    strftime(time_string, sizeof(time_string), "%Y-%m-%d %H:%M:%S", localtime(&t));
    log_fs << "[" << time_string << "] " << log_head << " " << log_body << std::endl;
}

void handler(int s) {
    log("[Info]", "Server exit!");
    exit(0);
}

void daemonize() {
    pid_t pid;
    int fd;
    if ((pid = fork()) < 0) {
        std::cerr << "[Error] can't fork!" << std::endl;
    } else if (pid != 0) {
        exit(0);
    }
    setsid();
    if ((fd = open("/dev/null", O_RDWR)) != -1) {
        dup2(fd, STDIN_FILENO);
        dup2(fd, STDOUT_FILENO);
        dup2(fd, STDERR_FILENO);
        if (fd > STDERR_FILENO) {
            close(fd);
        }
    }
}

void init_network(int port) {
    log("[Info]", "Init network...");
    server_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    memset(&server_addr, 0, sizeof(server_addr));
    memset(&client_addr, 0, sizeof(client_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(port);
    server_addr_len = sizeof(server_addr);
    client_addr_len = sizeof(client_addr);
    SOCKET_HANDLE(bind(server_fd, (struct sockaddr *) &server_addr, server_addr_len));
    SOCKET_HANDLE(listen(server_fd, 10));
    log("[Info]", "Init network done.");
}


int main(int argc, char **argv) {
    if (argc != 3 || argv[1][0] != '-' || argv[1][1] != 'p') {
        std::cout << "[Usage] " << argv[0] << " -p <port>" << std::endl;
        return 0;
    }
    int port = atoi(argv[2]);
    daemonize();
    signal(SIGINT, handler);
    log_fs.open("log.txt", std::ofstream::out | std::ofstream::app);
    init_network(port);
    for (;;) {
        SOCKET_HANDLE(client_fd = accept(server_fd, (struct sockaddr *) &client_addr, &client_addr_len));
        std::string data = "hello world";
        log("[Info]", "Client connected.");
        SOCKET_HANDLE(send(client_fd, data.c_str(), data.length(), 0));
        close(client_fd);
    }
    // never touch
    return 0;
}
