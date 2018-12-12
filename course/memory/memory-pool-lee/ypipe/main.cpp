#include "ypipe.hpp"
#include <stdio.h>

int main(int argc, char** argv)
{
    zmq::ypipe_t<int, 65535> queue;
    
    queue.write(10, true);
    queue.write(20, true);
    queue.write(30, false);
    queue.flush();
    
    int value = 0;
    while(queue.read(&value))
    {
        printf("readed value is %d \n", value);
    }
    
    return 0;
}