#include <iostream>
#include <signal.h>
#include <errno.h>
#include <sys/types.h>

int main (int argc, char** argv) {
    if (argc != 3) {
        std::cout << "[Usage] kill <signal number> <target pid>" << std::endl;
        return 0;
    }
    int signal_number = atoi(argv[1]);
    pid_t target_pid = atoi(argv[2]);
    if (target_pid <= 0) {
        std::cerr << "[Error] Invalid pid: " << target_pid << std::endl;
        return 1;
    }
    if (kill(target_pid, signal_number) != 0) {
        switch (errno) {
            case EINVAL:
                std::cerr << "[Error] Invalid signal number: " << signal_number << std::endl;
                return 1;
            case EPERM:
                std::cerr << "[Error] Permission denied!" << std::endl;
                return 1;
            case ESRCH:
                std::cerr << "[Error] Process does not exist pid=" << target_pid << std::endl;
                return 1;
            default:
                std::cerr << "[Error] Unknown error: " << errno << std::endl;
                return 1;
        }
    }
    return 0;
}

