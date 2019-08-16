#include <cstring>
#include <utility>
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include "network.h"

network::network() {
    this->_initialize_socket();
}

network::network(const char *const ip, uint16_t port) : _ip(ip), _port(port) {
    this->_initialize_socket();
    this->_initialize_socket_address();
}

network::network(std::string ip, uint16_t port) : _ip(std::move(ip)), _port(port) {
    this->_initialize_socket();
    this->_initialize_socket_address();
}

network::network(const int socket, const struct sockaddr_in *const socket_address) : _socket(socket) {
    this->_socket_address_length = sizeof(this->_socket_address);
    memcpy(&this->_socket_address, socket_address, this->_socket_address_length);
    this->_ip = inet_ntoa(this->_socket_address.sin_addr);
    this->_port = ntohs(this->_socket_address.sin_port);
}

void network::set_address(const std::string &ip, const uint16_t port) {
    this->_ip = ip;
    this->_port = port;
    this->_initialize_socket_address();
}

int network::listen(const int backlog) {
    if (bind(this->_socket, (struct sockaddr *) &this->_socket_address, this->_socket_address_length) == -1) {
        return -1;
    } else {
        return ::listen(this->_socket, backlog);
    }
}

network network::accept() {
    struct sockaddr_in client_socket_address{};
    socklen_t client_socket_address_length = sizeof(client_socket_address);
    int client_socket = ::accept(this->_socket, (struct sockaddr *) &client_socket_address, &client_socket_address_length);
    network client(client_socket, &client_socket_address);
    return client;
}

int network::connect() {
    return ::connect(this->_socket, (struct sockaddr *) &this->_socket_address, this->_socket_address_length);
}

int network::out(const char *const buffer, const size_t size) const {
    return send(this->_socket, buffer, size, 0);
}

int network::out(const char *const text) const {
    return this->out(text, strlen(text));
}

int network::out(const std::string &text) const {
    return this->out(text.c_str(), text.length());
}

int network::in(char *const buffer, const size_t size) {
    return recv(this->_socket, buffer, size, 0);
}

int network::block() {
    int mode = fcntl(this->_socket, F_GETFL, 0);
    return mode == -1 ? -1 : fcntl(this->_socket, F_SETFL, mode | O_NONBLOCK);
}

int network::non_block() {
    int mode = fcntl(this->_socket, F_GETFL, 0);
    return mode == -1 ? -1 : fcntl(this->_socket, F_SETFL, mode & (~O_NONBLOCK));
}

int network::close() {
    return ::close(this->_socket);
}

int network::shutdown(const int how) {
    return ::shutdown(this->_socket, how);
}

int network::socket() const {
    return this->_socket;
}

const std::string &network::ip() const {
    return this->_ip;
}

uint16_t network::port() const {
    return this->_port;
}

int network::error_number() const {
    return errno;
}

std::string network::error_string() const {
    return std::string(std::strerror(errno));
}

void network::_initialize_socket() {
    this->_socket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (this->_socket > 0) {
        int allow_reuse = 1;
        setsockopt(this->_socket, SOL_SOCKET, SO_REUSEADDR, &allow_reuse, sizeof(allow_reuse));
    }
}

void network::_initialize_socket_address() {
    this->_socket_address_length = sizeof(this->_socket_address);
    memset(&this->_socket_address, 0, this->_socket_address_length);
    this->_socket_address.sin_family = AF_INET;
    this->_socket_address.sin_addr.s_addr = inet_addr(this->_ip.c_str());
    this->_socket_address.sin_port = htons(this->_port);
}
