//
// Created by Yair on 04/04/2022.
//
#include "Respond.h"

int respondSwitch(respondHeader resHeader, char* payload, uint32_t payloadSize, signRequest signReq){
    Tools tools = Tools();
    //Tools::meInfo clientInfo = tools.readClientInfo();

    if (resHeader.code == SIGN_SUCCESS){
        unsigned char *userId;
        memcpy_s(userId, 16, payload, 16);
        printf("Sign up succeeded!");
        printf("clients ID is %s", userId);

        // now I'll save the data into the file
        std::string dataToFile = signReq.name;
        dataToFile += '\n';
        dataToFile += tools.hexStrToStr(userId, ID_LEN) + '\n';
        dataToFile += signReq.publicKey;
        return tools.writeToFile("me.info", dataToFile);
    }

    if (resHeader.code == USERS_LIST){

    }

    if (resHeader.code == PUB_KEY){
        PubKeyPayload respondData{};
        respondData.ID = payload;
        respondData.pubKey = payload + 16;
        printf("\nThe server successfully responded to request\n ");
        printf("Here is the public key of MessageU user ID %s", respondData.ID);
    }

    if (resHeader.code == MESSAGE_SENT){ // TODO: change variable names

    }

    if (resHeader.code == EXTRACT_MESSAGES){

    }

    if (resHeader.code == ERROR_CODE){

    }

    return 1;
}
