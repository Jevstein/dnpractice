#ifndef LOONG_EVENT_H
#define LOONG_EVENT_H

#include <sys/epoll.h>
#include <vector>
#include "network.h"

class event {
public:
    explicit event(int max_events = 100);

    int control_event(int fd, int option, uint32_t events);

    int control_event(const network *n, int option, uint32_t events);

    int add_event(int fd, uint32_t events);

    int add_event(const network *n, uint32_t events);

    int modify_event(int fd, uint32_t events);

    int modify_event(const network *n, uint32_t events);

    int delete_event(int fd);

    int delete_event(const network *n);

    [[nodiscard]] const struct epoll_event &next(int timeout);

    int close();

    [[nodiscard]] int events_count() const;

private:
    int _epoll;
    int _max_events;
    std::vector<struct epoll_event> _events_list;
    int _events_count;
    int _current_index;
};


#endif //LOONG_EVENT_H
