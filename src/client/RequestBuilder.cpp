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

RequestBuilder::reqTuple RequestBuilder::buildReq(ClientUi::uiData userData) {
    if (userData.reqCode == 110){
        // TODO: test this
        uReq.signReq = signRequest();
        strcpy(uReq.signReq.clientId, userData.userId);
        strcpy(uReq.signReq.name,  userData.userName);
        strcpy(uReq.signReq.publicKey,  "This is public key. replace me to the real shit!!");
        // TODO: strcpy is not safe
        // TODO: assign the right public key.

        retReqTuple.uRequest = uReq;
        retReqTuple.requestLength = uReq.signReq.payloadSize + HEADER_LEN;

        return retReqTuple;
    }

    Tools tools = Tools();
    Tools::meInfo clientInfo = tools.readClientInfo();

    if (userData.reqCode == 120){
        // TODO: test this
        uReq.usLiReq = usersListRequest();
        strcpy(uReq.usLiReq.clientId,  clientInfo.clientID.c_str());
        // TODO: strcpy is not safe
        // TODO: assign the other fields of the request.

        retReqTuple.uRequest = uReq;
        retReqTuple.requestLength = sizeof(uReq.usLiReq);
    }

    if (userData.reqCode == 130){
        // TODO: test this
        uReq.pubKeyReq = publicKeyRequest();
        strcpy(uReq.pubKeyReq.destUserId,  userData.userId);
        strcpy(uReq.pubKeyReq.clientId,clientInfo.clientID.c_str());

        // TODO: strcpy is not safe

        retReqTuple.uRequest = uReq;
        retReqTuple.requestLength = sizeof(uReq.pubKeyReq);
    }

    if (userData.reqCode == 140){
        // TODO: test this
        uReq.getMsgsReq = getMessagesRequest();
        strcpy(uReq.getMsgsReq.clientId, clientInfo.clientID.c_str());
        // TODO: strcpy is not safe

        retReqTuple.uRequest = uReq;
        retReqTuple.requestLength = sizeof(uReq.getMsgsReq);
    }

    if (userData.reqCode == 150){
        // TODO: test this
        uReq.sendMsgReq = sendMessageRequest();
        strcpy(uReq.sendMsgReq.destUserId,  userData.userId);
        strcpy(uReq.sendMsgReq.clientId, clientInfo.clientID.c_str());
        strcpy(uReq.sendMsgReq.messageContent,  userData.messageText);  // TODO: implement encryption.
        uReq.sendMsgReq.messageType =  userData.messageType;
        uReq.sendMsgReq.contentSize = strlen((userData.messageText));


        // TODO: strcpy is not safe

        retReqTuple.uRequest = uReq;
        retReqTuple.requestLength = sizeof(uReq.getMsgsReq);
    }

    if (userData.reqCode == 151){
        // TODO: test this
        uReq.sendMsgReq = sendMessageRequest();
        strcpy(uReq.sendMsgReq.destUserId,  userData.userId);
        strcpy(uReq.sendMsgReq.clientId, clientInfo.clientID.c_str());
        strcpy(uReq.sendMsgReq.messageContent,  userData.messageText); // TODO: implement symmetric key.
        uReq.sendMsgReq.messageType =  userData.messageType;
        uReq.sendMsgReq.contentSize = strlen((userData.messageText));
        // TODO: strcpy is not safe

        retReqTuple.uRequest = uReq;
        retReqTuple.requestLength = sizeof(uReq.getMsgsReq);
    }

    if (userData.reqCode == 152){
        // TODO: test this
        uReq.sendMsgReq = sendMessageRequest();
        strcpy(uReq.sendMsgReq.destUserId,  userData.userId);
        strcpy(uReq.sendMsgReq.clientId, clientInfo.clientID.c_str());
        strcpy(uReq.sendMsgReq.messageContent,  userData.messageText); // TODO: implement key
        uReq.sendMsgReq.messageType =  userData.messageType;
        uReq.sendMsgReq.contentSize = strlen((userData.messageText));
        // TODO: continue here - add client ID of the destination client!
        // TODO: strcpy is not safe

        retReqTuple.uRequest = uReq;
        retReqTuple.requestLength = sizeof(uReq.getMsgsReq);
    }


    return retReqTuple;


}
