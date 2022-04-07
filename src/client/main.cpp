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
    ClientUi ui = ClientUi();
    userData = ui.userIntention();

    RequestBuilder rb = RequestBuilder();

    RequestBuilder::reqTuple requestTuple = rb.buildReq(userData);
    // RequestBuilder::reqTuple requestTuple = rb.buildReq(userData.reqCode, userData.userName, userData.messageText);

        // TODO: insert to the final report - strcpy is an unsafe function.
        //  When you try to copy a string using strcpy() to a buffer which is not
        //  large enough to contain it, it will cause a buffer overflow.

    ClientConnect clientconn = ClientConnect();
    clientconn.mainConnection(&(requestTuple.uRequest.buffer), requestTuple.requestLength, requestTuple.uRequest.signReq);

}