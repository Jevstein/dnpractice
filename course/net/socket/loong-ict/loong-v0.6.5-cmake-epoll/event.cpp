#include <unistd.h>
#include "event.h"

event::event(int max_events) : _max_events(max_events) {
    this->_epoll = epoll_create(1);
    this->_events_list.reserve(this->_max_events);
    this->_events_list.resize(this->_max_events);
    this->_events_count = -1;
    this->_current_index = 0;
}

int event::control_event(const int fd, const int option, const uint32_t events) {
    struct epoll_event temp_event{};
    temp_event.data.fd = fd;
    temp_event.events = events;
    return epoll_ctl(this->_epoll, option, fd, &temp_event);
}

int event::control_event(const network *n, const int option, const uint32_t events) {
    struct epoll_event temp_event{};
    temp_event.data.ptr = (void *) n;
    temp_event.events = events;
    return epoll_ctl(this->_epoll, option, n->socket(), &temp_event);
}

int event::add_event(const int fd, const uint32_t events) {
    return this->control_event(fd, EPOLL_CTL_ADD, events);
}

int event::add_event(const network *n, const uint32_t events) {
    return this->control_event(n, EPOLL_CTL_ADD, events);
}

int event::modify_event(const int fd, const uint32_t events) {
    return this->control_event(fd, EPOLL_CTL_MOD, events);
}

int event::modify_event(const network *n, const uint32_t events) {
    return this->control_event(n, EPOLL_CTL_MOD, events);
}

int event::delete_event(const int fd) {
    return this->control_event(fd, EPOLL_CTL_DEL, 0);
}

int event::delete_event(const network *n) {
    return this->control_event(n, EPOLL_CTL_DEL, 0);
}

const struct epoll_event &event::next(int timeout) {
    if (this->_current_index >= this->_events_count) {
        this->_events_count = epoll_wait(this->_epoll, this->_events_list.data(), this->_max_events, timeout);
        this->_current_index = 0;
    }
    return this->_events_list[this->_current_index++];
}

int event::close() {
    return ::close(this->_epoll);
}

int event::events_count() const {
    if (this->_events_count < 0) {
        return 0;
    } else {
        return this->_events_count - this->_current_index;
    }
}
