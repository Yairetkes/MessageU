//
// Created by Yair on 24/03/2022.
//
#include <string.h>

#include "RequestBuilder.h"

//TODO: do I need this constructor?
RequestBuilder::RequestBuilder() {

}

//TODO: do I need this constructor?
RequestBuilder::reqTuple::reqTuple() {

}

//TODO: do I need this constructor?
RequestBuilder::u_request::u_request() {

}

RequestBuilder::reqTuple RequestBuilder::buildReq(int reqCode, char *userName, char *messageText ) {
    if (reqCode == 110){
        // TODO: test this
        uReq.signReq = signRequest();
        strcpy(uReq.signReq.name,  userName);
        strcpy(uReq.signReq.publicKey,  "This is public key. replace me to the real shit!!");
        uReq.signReq.payloadSize = sizeof(uReq.signReq.name) + sizeof(uReq.signReq.publicKey);
        uReq.signReq.version = 1;
        uReq.signReq.code = 110;
        // TODO: strcpy is not safe
        // TODO: assign name from wherever name is coming from.
        // TODO: assign the right public key.

        retReqTuple.uRequest = uReq;
        retReqTuple.requestLength = uReq.signReq.payloadSize + sizeof(uReq.signReq);
    }

    if (reqCode == 120){
        // TODO: test this
        uReq.usLiReq = usersListRequest();
        strcpy(uReq.usLiReq.clientId,  "avi");
        // TODO: strcpy is not safe
        // TODO: assign clientId from wherever clientId is coming from.
        // TODO: assign the other fields of the request.

        retReqTuple.uRequest = uReq;
        retReqTuple.requestLength = uReq.usLiReq.payloadSize + sizeof(uReq.usLiReq);
    }



    return retReqTuple;


}
