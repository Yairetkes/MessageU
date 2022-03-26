//
// Created by Yair on 19/03/2022.
//

#ifndef UNTITLED_CLIENTUI_H
#define UNTITLED_CLIENTUI_H

#include <iostream>

const int MESSAGE_MAX_LEN = 1001;

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

public:
    struct uiData{
        int reqCode;
        char userName[255];
        char messageText[MESSAGE_MAX_LEN];
    };

    int userIntention();


};


#endif //UNTITLED_CLIENTUI_H
