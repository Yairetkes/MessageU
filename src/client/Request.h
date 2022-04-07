//
// Created by Yair on 20/03/2022.
//

#ifndef UNTITLED_REQUEST_H
#define UNTITLED_REQUEST_H

#pragma pack(push,1)

/*
 *
 * in this file we define the structs that represent requests,
 * every structure has it own unique fields as described in the instructions.
 * class RequestBuilder will use this file in order to well... build a struct.
 *
 * */

const int NAME_LEN = 255;
const int PUBLIC_KEY_LEN = 160;
const int HEADER_LEN = 23;
const int SIGN_REQ_LEN = NAME_LEN + PUBLIC_KEY_LEN; // without header!!
const int PUBLIC_KEY_SIZE = 16;
const int ID_LEN = 16;
const int MAX_MESSAGE_LEN = 1024;

// TODO: change the latter to the real value.
const char CURRENT_VERSION = 1;
#include <cstdint>

struct RequestHeader {
    char clientId[ID_LEN];
    uint8_t version;
    uint16_t code;
    uint32_t payloadSize;
    RequestHeader(){
        version = CURRENT_VERSION;
    }
};

struct signRequest: RequestHeader{
    char name[NAME_LEN];
    char publicKey[PUBLIC_KEY_LEN];
    signRequest(){
        code = 1100;
        payloadSize = SIGN_REQ_LEN;
    }
};

struct usersListRequest: RequestHeader{
    usersListRequest(){
        code = 1101;
        payloadSize = 0;
    }
};

struct publicKeyRequest: RequestHeader{
    char destUserId[ID_LEN];
    publicKeyRequest(){
        code = 1102;
        payloadSize = PUBLIC_KEY_SIZE;
    }
};

struct sendMessageRequest: RequestHeader{
    char destUserId[ID_LEN];
    uint8_t messageType;
    uint32_t contentSize;
    char messageContent[MAX_MESSAGE_LEN];
    // TODO: should support end to end decryption.
    sendMessageRequest(){
        code = 1103;
    }
};

struct getMessagesRequest: RequestHeader{
    getMessagesRequest(){
        payloadSize = 0;
        code = 1104;
    }
};


#pragma pack(pop)

#endif //UNTITLED_REQUEST_H
