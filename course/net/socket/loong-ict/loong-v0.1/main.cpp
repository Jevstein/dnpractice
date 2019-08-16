#include <iostream>
#include <string>
#include <unordered_map>
#include <csignal>
#include "server.h"
#include "event.h"
#include "network.h"
#include "log.h"

void handler(int s) {
    log("[Info]", "Server exit!");
    exit(0);
}

std::string request(network &n) {
    const int buffer_size = 1024;
    char buffer[1024];
    HANDLE(n.in(buffer, buffer_size));
    return std::string(buffer);
}

void response(network &n, const std::string &data) {
    std::string http_data = "HTTP/1.1 200 OK\r\nServer: loong\r\nContent-type: text/html\r\n\r\n" + data;
    HANDLE(n.out(http_data));
    n.shutdown(SHUT_RDWR);
}

int main(int argc, char **argv) {
    if (argc != 3 || argv[1][0] != '-' || argv[1][1] != 'p') {
        std::cout << "[Usage] " << argv[0] << " -p <port>" << std::endl;
        return 0;
    }
    int port = (int) strtol(argv[2], nullptr, 10);
    daemonize();
    signal(SIGINT, handler);
    pid_t server_pid;
    while ((server_pid = server_singleton()) != -1) {
        kill(server_pid, SIGINT);
    }
    log("[Info]", "Server start!");
    std::unordered_map<int, network> clients;
    network server("0.0.0.0", port);
    event server_event;
    HANDLE(server.listen(10));
    HANDLE(server.non_block());
    HANDLE(server_event.add_event(server.socket(), EPOLLIN));
    std::string http_text;
    for (;;) {
        struct epoll_event each_event = server_event.next(-1);
        if (each_event.data.fd == server.socket()) {
            network client = server.accept();
            client.non_block();
            clients[client.socket()] = client;
            log("[Info]", "Client connected: IP=" + client.ip() + " Port=" + std::to_string(client.port()));
            HANDLE(server_event.add_event(client.socket(), EPOLLIN | EPOLLET));
        } else if (each_event.events & EPOLLIN) {
            if (clients.count(each_event.data.fd) > 0) {
                network &client = clients[each_event.data.fd];
                http_text = request(client);
                HANDLE(server_event.modify_event(client.socket(), EPOLLOUT | EPOLLET));
            }
        } else if (each_event.events & EPOLLOUT) {
            if (clients.count(each_event.data.fd) > 0) {
                network &client = clients[each_event.data.fd];
                response(client, http_text);
                HANDLE(server_event.delete_event(client.socket()));
                client.close();
            }
        } else {
            log("[Warn]", "Unknown events: " + std::to_string(each_event.events));
        }
    }
    return 0;
}