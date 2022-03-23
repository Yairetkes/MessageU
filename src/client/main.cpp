#include "ClientConnect.h"
#include "ClientUi.h"
#include "Request.h"
#include "Tools.h"

#include <cstring>
#include <cstdio>
#include <cstdlib>

// TODO: remove __cdecl ?
int __cdecl main(int argc, char **argv)
{
    int requestVal = 0;
//    Tools tool = Tools();
    ClientUi ui = ClientUi();
    requestVal = ui.userIntention();
    printf("requestVal = %d\n", requestVal);

    signRequest request = signRequest();
    if (requestVal == 110) {
        request = signRequest();
        std::strcpy(request.clientId, "1234");
//        std::memcpy(&request.version, "1", 1);
        request.version = 1;
        std::memcpy(&request.code, "110", 2);
        request.payloadSize = 415;
//        std::memcpy(&request.payloadSize, 415, 4);
        std::strcpy(request.name, "Avi");
        std::strcpy(request.publicKey, "This is public key... RCA#$BR%");
        // TODO: insert to the final report - strcpy is a unsafe function.
        //  When you try to copy a string using strcpy() to a buffer which is not
        //  large enough to contain it, it will cause a buffer overflow.
    }

    // creating a new request object and passing the parameter of the request value (and other needed
    // parameters) to it.

    union u_struct{
        signRequest req;
        char buffer;
    } uReq;

//    u_struct u_req = u_struct();
    //uReq.buffer = 'a';
    uReq.req = request;

    ClientConnect clientconn = ClientConnect();
    clientconn.mainConnection(&(uReq.buffer));

}