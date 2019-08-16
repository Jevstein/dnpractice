#include <signal.h>
#include <unistd.h>
#include <iostream>

sigset_t new_set, old_set, pending_set;

void signal_handler (int signal_number)
{
    switch (signal_number) {
        case SIGTSTP:
            std::cout << "Bye!" << std::endl;
            exit(0);
        case SIGHUP:
            std::cout << "Restore mask." << std::endl;
            sigsuspend(&old_set);
            break;
        case SIGINT:
            std::cout << "Get SIGINT!!!" << std::endl;
    }
}

int main ()
{
    // block SIGINT信号
    sigemptyset(&new_set);
    sigaddset(&new_set, SIGINT);
    sigprocmask(SIG_SETMASK, &new_set, &old_set);
    signal(SIGTSTP, signal_handler);
    signal(SIGHUP, signal_handler);
    signal(SIGINT, signal_handler);
    for (;;) {
        sigpending(&pending_set);
        if (sigismember(&pending_set, SIGINT)) {
            std::cout << "SIGINT pending!!!" << std::endl;
        } else {
            std::cout << "SIGINT not come..." << std::endl;
        }
        sleep(1);
    }
}
