#include <zmq.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#define MAX_BUFFER_LEN 1024

int main (void)
{
    printf ("Connecting to hello world server…\n");
    void *context = zmq_ctx_new ();
    void *requester = zmq_socket (context, ZMQ_REQ);
    if (0 != zmq_connect (requester, "tcp://localhost:8080"))
    {
        perror("connect server failed.");
    }

    char buffer [MAX_BUFFER_LEN] = {0};
    printf ("Send Hello to server.\n");
    zmq_send (requester, "Hello", 5, 0);
    zmq_recv (requester, buffer, 10, 0);
    printf ("Received %s.\n", buffer);
    zmq_close (requester);

    zmq_ctx_destroy (context);
    
    return 0;
}

