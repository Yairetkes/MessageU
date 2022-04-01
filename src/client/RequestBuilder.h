//
// Created by Yair on 24/03/2022.
//

#ifndef UNTITLED_REQUESTBUILDER_H
#define UNTITLED_REQUESTBUILDER_H

#include "Request.h"
# include "ClientUi.h"

class RequestBuilder {
public:
    // This union will contain the request structs, but only the desired struct will be initialized.
    union u_request{
        signRequest signReq;
        usersListRequest usLiReq;
        publicKeyRequest pubKeyReq;
        sendMessageRequest sendMsgReq;
        getMessagesRequest getMsgsReq;
        char buffer;

        u_request();
    } uReq;

    // The struct which returned from function buildReq().
    struct reqTuple{
        reqTuple();

        u_request uRequest;
        int requestLength;
    }retReqTuple;

    RequestBuilder();

    // this function really is building the struct.
    reqTuple buildReq(ClientUi::uiData userData);


};


#endif //UNTITLED_REQUESTBUILDER_H
