//
// Created by Yair on 13/03/2022.
//

#include "ClientConnect.h"

    int ClientConnect::mainConnection(char *reqPtr, int bufferLength, signRequest signReq){

            int headerLength = 23;
            // Initialize Winsock
            iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
            if (iResult != 0) {
                printf("WSAStartup failed with error: %d\n", iResult);
                return 1;
            }

            ZeroMemory(&hints, sizeof(hints));
            hints.ai_family = AF_UNSPEC;
            hints.ai_socktype = SOCK_STREAM;
            hints.ai_protocol = IPPROTO_TCP;

            Tools::serverInfo connectionInfo;
            Tools tools = Tools();
            connectionInfo = tools.readServerInfo();

            // Resolve the server address and port
            iResult = getaddrinfo(connectionInfo.ip.c_str(), connectionInfo.host.c_str(), &hints, &result);
            if ( iResult != 0 ) {
                printf("geta    ddrinfo failed with error: %d\n", iResult);

                WSACleanup();

                return 1;
            }

            // Attempt to connect to an address until one succeeds
            for(
            ptr = result;
            ptr != NULL;
            ptr = ptr->ai_next
            ) {

                // Create a SOCKET for connecting to server
                ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
                                       ptr->ai_protocol);
                if (ConnectSocket == INVALID_SOCKET) {
                    printf("socket failed with error: %ld\n",

                           WSAGetLastError()

                    );

                    WSACleanup();

                    return 1;
                }

                // Connect to server.
                iResult = connect(ConnectSocket, ptr->ai_addr, (int) ptr->ai_addrlen);
                if (iResult == SOCKET_ERROR) {
                    closesocket(ConnectSocket);
                    ConnectSocket = INVALID_SOCKET;
                    continue;
                }
                break;
            }

            freeaddrinfo(result);

            if (ConnectSocket == INVALID_SOCKET) {
                printf("Unable to connect to server!\n");

                WSACleanup();

                return 1;
            }

            // Send an initial buffer
        iResult = send(ConnectSocket, reqPtr,bufferLength , 0);
        if (iResult == SOCKET_ERROR) {
                printf("send failed with error: %d\n",

                       WSAGetLastError()

                );
                closesocket(ConnectSocket);

                WSACleanup();

                return 1;
            }

            printf("Bytes Sent: %ld\n", iResult);

            // shutdown the connection since no more data will be sent
            iResult = shutdown(ConnectSocket, SD_SEND);
            if (iResult == SOCKET_ERROR) {
                printf("shutdown failed with error: %d\n",

                       WSAGetLastError()

                );
                closesocket(ConnectSocket);

                WSACleanup();

                return 1;
            }

        respondBuffer resBuf = respondBuffer();

            // Receive until the peer closes the connection
            do {
                iResult = recv(ConnectSocket, resBuf.buffer, sizeof(respondHeader), 0);
                if (iResult > 0) {

                    char* payload = new char[resBuf.resHeader.payloadSize];
                    int iResult = recv(ConnectSocket, payload, resBuf.resHeader.payloadSize, 0);
                    respondSwitch(resBuf.resHeader, payload, resBuf.resHeader.payloadSize, signReq);

                    //printf("Bytes received: %d\n", iResult);
                    //printf("message received: \n%d\n", *recvbuf);
                }
                else if ( iResult == 0 )
                    printf("Connection closed\n");
                else
                    printf("recv failed with error: %d\n",

                           WSAGetLastError()

                    );

            } while( iResult > 0 );

            // cleanup
            closesocket(ConnectSocket);

            WSACleanup();

            return 0;
    }