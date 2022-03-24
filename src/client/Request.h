//
// Created by Yair on 20/03/2022.
//

#ifndef UNTITLED_REQUEST_H
#define UNTITLED_REQUEST_H

#pragma pack(push,1)
struct RequestHeader {
    char clientId[16];
    unsigned char version;
    unsigned short code;
    unsigned int payloadSize;
};

struct signRequest: RequestHeader{
    char name[255];
    char publicKey[160];
};

struct usersListRequest: RequestHeader{
    usersListRequest(){
        payloadSize = 0;
    }
};
// TODO: add other requests structs...

#pragma pack(pop)

#endif //UNTITLED_REQUEST_H
