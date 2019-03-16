#include <zmq.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>

#define MAX_BUFFER_LEN 1024

int main (void)
{
    //  Socket to talk to clients
    void *context = zmq_ctx_new ();
    void *responder = zmq_socket (context, ZMQ_REP);
    int rc = zmq_bind (responder, "tcp://*:8080");
    assert (rc == 0);

    while (1) 
    {
        char buffer [MAX_BUFFER_LEN] = {0};
        zmq_recv (responder, buffer, 10, 0);
        printf ("%s.\n", buffer);
        sleep (1);
        zmq_send (responder, "World", 5, 0);
        printf("send world to client.\n");
    }

    return 0;
}

