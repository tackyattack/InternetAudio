//
//  main.cpp
//  InternetAudio
//
//  Created by HENRY BERGIN on 7/28/17.
//  Copyright © 2017 Henry Bergin. All rights reserved.
//


// Create abstraction classes / libraries so that it's easy to port.
// For example, create an system audio class that contains the needed
// functions for a higher level audio manager. For example, writing audio buffers
// would go in the lower level system audio class.

// todo: first create a thread based and usec timed audio over IP simulator
//       that you can use to simulate the TCP / UDP connection to get the
//       audio sync algorithm up and running properly. Make sure the "input"
//       buffer is filled at the correct sample rate, otherwise the buffers
//       will under/over flow more than it actually would with just the clock
//       drifting.

// Server side: block until a set amount of samples is created. (make sure buffer is still filling in background)
// Client side: do not block for now. One solution to taking care of jitter is to have a predefined delay
//              that is scaled on the client side to match what it actually should've been to make sure buffer
//              doesn't under/over flow.
//              Virtual software clocks shouldn't be needed unless the input/output need to have close to no latency.
//              Buffering takes care of this problem but introduces some latency, which should be fine since this
//              app just needs "mostly" on time audio.


// links:
// 1. http://www.binarytides.com/socket-programming-c-linux-tutorial/

#include "port_audio_test.h"

#include <iostream>
#include <sys/time.h>
#include <sys/socket.h> // socket library
#include <sys/types.h>  // useful system types
#include <netinet/in.h> // contains internet address types
#include <arpa/inet.h>  // IPv4 address manipulation
#include <netdb.h>

#include <stdio.h>
#include <stdlib.h>

using namespace std;

uint32_t get_usec(struct timeval program_start)
{
    uint32_t time_usec_start = 0;
    uint32_t time_usec_current = 0;
    uint32_t time_usec_return = 0;
    
    struct timeval tv_program_current;
    gettimeofday(&tv_program_current, NULL);
    
    time_usec_start = (uint32_t)((program_start.tv_sec * 1000000) + program_start.tv_usec);
    time_usec_current = (uint32_t)((tv_program_current.tv_sec * 1000000) + tv_program_current.tv_usec);
    
    time_usec_return = time_usec_current - time_usec_start;
    
    return time_usec_return;
    
}

//-------TESTING-------

//---------------------

int main(int argc, const char * argv[]) {
    
//    
//    struct timeval tv_program_start;
//    
//    gettimeofday(&tv_program_start, NULL);
//    
//    ptest::startTest();
//    
//    while(1)
//    {
//        cout << "microsecond time:" << get_usec(tv_program_start) << endl;
//    }
    
    int err = 0;
    
    int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_IP); // AF_INET : IPv4  SOCK_STREAM : TCP  IPPROTO_IP : use the IP protocol
    
    if (sock < 0)
        cout << "error: could not create socket" << endl;
    else
        cout << "socket created" << endl;
    
    
    struct sockaddr_in server;
    
    server.sin_addr.s_addr = inet_addr("172.217.8.174");
    server.sin_family = AF_INET;
    server.sin_port = htons(80);
    
    err = connect(sock ,(struct sockaddr *)&server, sizeof(server));
    
    if (err < 0)
    {
        cout << "error: could not connect" << endl;
    }
    else
    {
        cout << "socket connected" << endl;
    }
    
    char message[] = "GET / HTTP/1.1\r\n\r\n";
    err = (int)send(sock,message,strlen(message), 0);
    if(err < 0)
    {
        cout << "error: send failed" << endl;
    }
    else
    {
        cout << "data send" << endl;
    }

    char server_buffer[100] = {0};
    
    // TCP is a stream of bytes, so treat it as such
    while(recv(sock, server_buffer, sizeof(server_buffer), 0) > 0)
    {
        printf("%s",server_buffer);
    }
    
    
    return 0;
}

