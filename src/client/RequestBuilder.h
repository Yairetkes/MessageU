//
// Created by Yair on 24/03/2022.
//

#ifndef UNTITLED_REQUESTBUILDER_H
#define UNTITLED_REQUESTBUILDER_H

#include "Request.h"


class RequestBuilder {
public:
    union u_request{
        signRequest signReq;
        usersListRequest usLiReq;
        // TODO: add other requests...
        char buffer;

        u_request();
    } uReq;

    struct reqTuple{
        reqTuple();

        u_request uRequest;
        int requestLength;
    }retReqTuple;

    RequestBuilder();

    reqTuple buildReq(int reqCode);


};


#endif //UNTITLED_REQUESTBUILDER_H
