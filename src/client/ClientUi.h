//
// Created by Yair on 19/03/2022.
//

#ifndef UNTITLED_CLIENTUI_H
#define UNTITLED_CLIENTUI_H

#include <iostream>
#include <cstdio>
#include <string>
#include <stdlib.h>
#include <string.h>
#include <fstream>

const int MESSAGE_MAX_LEN = 1024 - 23;
const int Max_NAME_LEN = 255;
const int ID_LENGTH = 16;
const std::string FILE_NAME = "me.info";

// This claas handles with user's UI.
class ClientUi {
    // should be compatible with this variable at file Request.py on server (minus header
    // which is 23 bytes long)
    int requestLength = 3;
    // TODO: add encapsulation (private and public) to all class's methods and fields.
    const char *uiMessage = "MessageU client at your service.\n"
                            "110) Register\n"
                            "120) Request for clients list\n"
                            "130) Request for public key\n"
                            "140) Request for waiting messages\n"
                            "150) Send a text message\n"
                            "151) Send a request for symmetric key\n"
                            "152) Send your symmetric key\n"
                            "0) Exit client\n"
                            "?";

    const char *signingMessage = "Please enter user name:";
    const char *publicKeyMessage = "Please enter the ID of the user you wish to get his public key";

public:

    struct uiData{
        int reqCode;
        char userName[Max_NAME_LEN];
        char userId[ID_LENGTH];
        char messageText[MESSAGE_MAX_LEN];
        int messageType;
    } userData;

    uiData userIntention();


};


#endif //UNTITLED_CLIENTUI_H
