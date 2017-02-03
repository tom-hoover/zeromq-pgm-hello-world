

//  Weather update server
//  Binds PUB socket to tcp://*:5556
//  Publishes random weather updates

#include "zhelpers.h"

int main (void)
{

    //  Prepare our context and publisher
    void *context = zmq_ctx_new ();
    void *publisher = zmq_socket (context, ZMQ_PUB);
    //int rc = zmq_bind (publisher, "tcp://*:5556"); assert (rc == 0);
    int hops = 128;
    int rc = zmq_setsockopt( publisher, ZMQ_MULTICAST_HOPS, &hops, sizeof hops ); assert (rc==0);    
    rc = zmq_connect(publisher, "norm://enp0s3;239.192.1.1:5555"); assert (rc == 0);



    //  Initialize random number generator
    srandom ((unsigned) time (NULL));
        int count = 0;    
    while (count<100) {
        printf( "count: %d\n", count );


        //  Send message to all subscribers
        char update [20];
        sprintf (update, "%d", count++);
        s_send (publisher, update);
        //sleep(1);

    }
    zmq_close (publisher);
    zmq_ctx_destroy (context);
    return 0;
}
