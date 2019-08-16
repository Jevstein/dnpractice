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

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cout << "[Usage] " << argv[0] << " <port>" << std::endl;
        return 0;
    }
    struct sockaddr_in addr;
    socklen_t addr_len;
    int fd = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP);
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(atoi(argv[1]));
    addr_len = sizeof(addr);
    SOCKET_HANDLE(connect(fd, (struct sockaddr *)&addr, addr_len));
    const int buffer_size = 100;
    char receive_buffer[buffer_size];
    int size;
    SOCKET_HANDLE(size = recv(fd, receive_buffer, buffer_size, 0));
    std::cout << "[Receive: size] " << receive_buffer << std::endl;
    close(fd);
    return 0;
}
