//
//  socket.hpp
//
//  Created by Johnathan Chiu on 2/21/19.
//  Copyright © 2019 Johnathan Chiu. All rights reserved.
//

#ifndef socket_hpp
#define socket_hpp

#include <stdio.h>
#include <iostream>
#include <cstring>
#if defined(__linux__)
    #include <arpa/inet.h>
    #include <sys/socket.h>
    #include <unistd.h>
#else
// comment
// release this when working on windows:
    #include <winsock2.h>
    #include <Ws2tcpip.h>
    #include <windows.h>

#pragma comment(lib, "Ws2_32.lib")
#endif

// need link with Ws2_32.lib
//#pragma comment(lib, "Ws2_32.lib")

#endif /* socket_hpp */

namespace serversock {

    struct objectData {
        unsigned int value;
    };

    void createConnection();
    int readValues(objectData *a);

}