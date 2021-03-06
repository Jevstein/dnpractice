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
#include <pthread.h>

#define SOCKET_HANDLE(X) \
    do { \
        if ((X) == -1) { \
            log("[Error]", strerror(errno)); \
            exit(1); \
        } \
    } while(0)

std::ofstream log_fs;
struct sockaddr_in server_addr;
socklen_t server_addr_len;
int server_fd;
const int thread_count = 10;
pthread_t thread[thread_count];

void log(std::string log_head, std::string log_body) {
    time_t t;
    time(&t);
    char time_string[32];
    strftime(time_string, sizeof(time_string), "%Y-%m-%d %H:%M:%S", localtime(&t));
    log_fs << "[" << time_string << "] " << log_head << " " << log_body << std::endl;
}

void handler(int s) {
    for (int i = 0; i < thread_count; i++) {
        pthread_cancel(thread[i]);
    }
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
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(port);
    server_addr_len = sizeof(server_addr);
    SOCKET_HANDLE(bind(server_fd, (struct sockaddr *) &server_addr, server_addr_len));
    SOCKET_HANDLE(listen(server_fd, 10));
    log("[Info]", "Init network done.");
}

std::string request(int fd)
{
    const int buffer_size =  2048;
    char buffer[buffer_size];
    memset(buffer, 0, buffer_size);
    int recv_index = 0;
    int scan_index = 0;
    for (;;) {
        int data_size = recv(fd, buffer + recv_index, buffer_size - recv_index, 0);
        if (data_size <= 0) {
            break;
        } else {
            recv_index += data_size;
            for (int i = scan_index; i < recv_index; i++) {
                if (buffer[i] == '\n') {
                    return std::string(buffer, i);
                }
            }
            scan_index = recv_index;
        }
    }
    return std::string(buffer);
}

void response(int fd, std::string data)
{
    std::string http_data = "HTTP/1.1 200 OK\r\nServer: loong\r\nContent-type: text/html\r\n\r\n" + data;
    SOCKET_HANDLE(send(fd, http_data.c_str(), http_data.length(), 0));
    shutdown(fd, 2);
}

void* thread_body(void* arg) {
    log("[Info]", "[Thread: " + std::to_string(pthread_self()) + "] Running!");
    struct sockaddr_in client_addr;
    socklen_t client_addr_len;
    memset(&client_addr, 0, sizeof(client_addr));
    client_addr_len = sizeof(client_addr);
    int client_fd;
    for (;;) {
        SOCKET_HANDLE(client_fd = accept(server_fd, (struct sockaddr *) &client_addr, &client_addr_len));
        log("[Info]", "[Thread: " + std::to_string(pthread_self()) + "] Client connected: IP=" + inet_ntoa(client_addr.sin_addr) + " Port=" + std::to_string(ntohs(client_addr.sin_port)));
        std::string rq = request(client_fd);
        rq += " Hello World !!!";
        response(client_fd, rq);
    }
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
    log("[Info]", "Server start!");
    init_network(port);
    for (int i = 0; i < thread_count; i++) {
        pthread_create(thread + i, nullptr, thread_body, nullptr);
    }
    for (;;) {
        pause();
    }
    // never touch
    return 0;
}
