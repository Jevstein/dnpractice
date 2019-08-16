#ifndef LOONG_NETWORK_H
#define LOONG_NETWORK_H

#include <string>
#include <arpa/inet.h>

class network {
public:
    network();

    network(const char *ip, uint16_t port);

    network(std::string ip, uint16_t port);

    network(int socket, const struct sockaddr_in *socket_addr);

    void set_address(const std::string &ip, uint16_t port);

    int listen(int backlog);

    [[nodiscard]] network accept();

    int connect();

    int out(const char *buffer, size_t size) const;

    int out(const char *text) const;

    int out(const std::string &text) const;

    int in(char *buffer, size_t size);

    int block();

    int non_block();

    int close();

    int shutdown(int how);

    [[nodiscard]] int socket() const;

    [[nodiscard]] const std::string &ip() const;

    [[nodiscard]] uint16_t port() const;

    [[nodiscard]] int error_number() const;

    [[nodiscard]] std::string error_string() const;

private:
    int _socket{};
    struct sockaddr_in _socket_address{};
    socklen_t _socket_address_length{};
    std::string _ip;
    uint16_t _port{};

    void _initialize_socket();

    void _initialize_socket_address();
};


#endif //LOONG_NETWORK_H
