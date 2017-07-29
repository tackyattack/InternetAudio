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

#include <iostream>
#include <sys/time.h>
#include <sys/socket.h>
#include "port_audio_test.h"

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
    
    
    struct timeval tv_program_start;
    
    gettimeofday(&tv_program_start, NULL);
    
    ptest::startTest();
    
    while(1)
    {
        cout << "microsecond time:" << get_usec(tv_program_start) << endl;
    }
    return 0;
}

