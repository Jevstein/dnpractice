#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstring>
#include <string>
#include <unistd.h>
#include <memory.h>

#define SOCKET_HANDLE(X) \
    do { \
        if ((X) == -1) { \
            std::cerr << "[Error] " << strerror(errno) << std::endl; \
            exit(1); \
        } \
    } while(0)

int main() {
    struct sockaddr_in server_addr, client_addr;
    socklen_t server_addr_len, client_addr_len;
    int server_fd = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP);
    int client_fd;
    memset(&server_addr, 0, sizeof(server_addr));
    memset(&client_addr, 0, sizeof(client_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(8080);
    server_addr_len = sizeof(server_addr);
    client_addr_len = sizeof(client_addr);
    SOCKET_HANDLE(bind(server_fd, (struct sockaddr *)&server_addr, server_addr_len));
    SOCKET_HANDLE(listen(server_fd, 10));
    for (;;) {
        SOCKET_HANDLE(client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_addr_len));
        std::string data = "hello world";
        SOCKET_HANDLE(send(client_fd, data.c_str(), data.length(), 0));
        close(client_fd);
    }
    // never touch.
    return 0;
}