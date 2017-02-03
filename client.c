

//  Weather update client
//  Connects SUB socket to tcp://localhost:5556
//  Collects weather updates and finds avg temp in zipcode

#include "zhelpers.h"

int main (int argc, char *argv [])
{
    int64_t mcastloop = 1;

    //  Socket to talk to server
    printf ("Collecting updates from weather server…\n");
    void *context = zmq_ctx_new ();
    void *subscriber = zmq_socket (context, ZMQ_SUB);
    //int rc = zmq_connect (subscriber, "tcp://localhost:5556"); assert (rc == 0);
    int rc = zmq_connect(subscriber, "epgm://enp0s3;239.192.1.1:5555"); assert (rc == 0);
    //int rc = zmq_connect(subscriber, "norm://enp0s3;239.192.1.1:5555"); assert (rc == 0);

    //  Subscribe to zipcode, default is NYC, 10001
    // char *filter = (argc > 1)? argv [1]: "10001 ";
    // Subscribe to everything
    char *filter = "";
    rc = zmq_setsockopt (subscriber, ZMQ_SUBSCRIBE, filter, strlen (filter));
    assert (rc == 0);
    
    //  Process 100 updates
    int update_nbr;
    long total_temp = 0;
    for (update_nbr = 0; update_nbr < 10000; update_nbr++) {
        char *string = s_recv (subscriber);
        printf( "%d: %s\n", update_nbr, string );  
        free(string);

    }

    zmq_close (subscriber);
    zmq_ctx_destroy (context);
    return 0;
}
