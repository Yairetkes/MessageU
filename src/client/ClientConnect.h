//
// Created by Yair on 13/03/2022.
//

#ifndef UNTITLED_CLIENTCONNECT_H
#define UNTITLED_CLIENTCONNECT_H

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#include <cstdio>

#include "Request.h"
#include "Tools.h"


// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "7000"

// TODO: add encapsulation (private and public) to all class's methods and fields.

class ClientConnect {
    WSADATA wsaData;
    SOCKET ConnectSocket = INVALID_SOCKET;
    struct addrinfo *result = NULL,
            *ptr = NULL,
            hints;
    const char *sendbuf = "this is a test";
    char recvbuf[DEFAULT_BUFLEN];
    int iResult;
    int recvbuflen = DEFAULT_BUFLEN;

public:
    int mainConnection(char *reqPtr, int bufferLength);

};


#endif //UNTITLED_CLIENTCONNECT_H
