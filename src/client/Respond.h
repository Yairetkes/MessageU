//
// Created by Yair on 04/04/2022.
//

#ifndef MESSAGEU_RESPOND_H
#define MESSAGEU_RESPOND_H

#include <cstdint>
#include "Tools.h"
#include "Request.h"

const int SIGN_SUCCESS = 2100;
const int USERS_LIST = 2101;
const int PUB_KEY = 2102;
const int MESSAGE_SENT = 2103;
const int EXTRACT_MESSAGES = 2104;
const int ERROR_CODE = 9000;

#pragma pack (push, 1)

    struct respondHeader {
        uint8_t version;
        uint16_t code;
        uint32_t payloadSize;
        respondHeader(){
            version = 1;
        }
    };
    union respondBuffer {
        respondHeader resHeader;
        char buffer[sizeof(respondHeader)];
        respondBuffer(){}
    };

    // will support parsing the respond
struct PubKeyPayload {
    char* ID;
    char* pubKey;
};

int respondSwitch(respondHeader resHeader, char* payload, uint32_t payloadSize, signRequest signReq);

#pragma pack (pop)

#endif //MESSAGEU_RESPOND_H
