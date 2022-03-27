#include "ClientConnect.h"
#include "ClientUi.h"
#include "Request.h"
#include "RequestBuilder.h"
#include "Tools.h"

#include <cstring>
#include <cstdio>
#include <cstdlib>

// TODO: remove __cdecl ?
int __cdecl main(int argc, char **argv)
{
    ClientUi::uiData userData;
//    Tools tool = Tools();
    ClientUi ui = ClientUi();
    userData = ui.userIntention();
    printf("userData.reqCode = %d", userData.reqCode);
    printf("userData.userName = %s", userData.userName);


    RequestBuilder rb = RequestBuilder();

    //signRequest request = signRequest();

    RequestBuilder::reqTuple requestTuple = rb.buildReq(userData.reqCode, userData.userName, userData.messageText);



//    if (requestCode == 110) {
//        request = signRequest();
//        std::strcpy(request.clientId, "1234");
////        std::memcpy(&request.version, "1", 1);
//        request.version = 1;
//        std::memcpy(&request.code, "110", 2);
//        request.payloadSize = 415;
////        std::memcpy(&request.payloadSize, 415, 4);
//        std::strcpy(request.name, "Avi");
//        std::strcpy(request.publicKey, "This is public key... RCA#$BR%");
        // TODO: insert to the final report - strcpy is a unsafe function.
        //  When you try to copy a string using strcpy() to a buffer which is not
        //  large enough to contain it, it will cause a buffer overflow.
//    }

    // creating a new request object and passing the parameter of the request value (and other needed
    // parameters) to it.

    // we insert the data into a union, because winsock send function accept const char pointer only.
//    union u_struct{
//        void *req;
//        char buffer;
//    } uReq;
//
////    u_struct u_req = u_struct();
//    //uReq.buffer = 'a';
//    uReq.req = &request;

    ClientConnect clientconn = ClientConnect();
    clientconn.mainConnection(&(requestTuple.uRequest.buffer), requestTuple.requestLength);

}