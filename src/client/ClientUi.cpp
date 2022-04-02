//
// Created by Yair on 19/03/2022.
//

#include "ClientUi.h"

ClientUi::uiData ClientUi::userIntention() {
    int input = -1;
    std::string strInput;

    while(input == -1) {
        printf(uiMessage);
        std::cin>>input;
        // TODO: check if cin considered safe (for the report). replace it or write about it...??
        if(input != -1)
            break;
    }

    std::cout << input << std::endl;
    // TODO: input validations.
    userData.reqCode =input;

    // it's a sign up request.
    if (input == 110){
        // checking if file me.info exist.
        std::ifstream f(FILE_NAME.c_str());
        // TODO: check if file exist. this check seem to not work, maybe becuse I didnt supply full path of file??
         if (!(f.good())) {
            printf(signingMessage);
            // Please enter user name:
             std::cin.ignore();
             std::getline(std::cin, strInput);
            while(strInput.length() > Max_NAME_LEN){
                printf("The user name entered is too long, please try again.\n");
                std::cin.ignore();
                std::getline(std::cin, strInput);
            }
            strcpy(userData.userName,strInput.c_str());
            // TODO: insert here public key?
             return userData;

        } else {// if file me.info exist.
            printf("Error! \nme.info file already exist.");
            exit(-1);
        }
    }

    // it's a request to get a list of all users.
    if (input == 120){
        return userData;
    }

    // it's a request to get the public key of a user.
    if (input == 130){
        printf(publicKeyMessage);
        std::cin.ignore();
        std::getline(std::cin, strInput);

        strcpy(userData.userId,strInput.c_str());

        return userData;
    }

    // it's a request to get waiting messages.
    if (input == 140){
        printf("You chosed to get waiting messages. the request is being sent now to server...\n");
        return userData;
    }

    // it's a request to send message to user.
    if (input == 150){
        userData.messageType = 3;
        printf("Please enter the user name of the client you wish to contact.\n");
        std::cin.ignore();
        std::getline(std::cin, strInput);
        strcpy(userData.userName,strInput.c_str());
        // TODO: input validations.

        printf("Please enter the text you wish to send to %s", strInput.c_str());
        printf( ":\n");
        std::getline(std::cin, strInput);
        strcpy(userData.messageText,strInput.c_str());
        // TODO: input validations.
        return userData;
    }

    // it's a request to get symmetric key.
    if (input == 151){
        userData.messageType = 1;
        printf("Please enter the user name of the client you wish to get key from.\n");
        std::cin.ignore();
        std::getline(std::cin, strInput);
        strcpy(userData.userName,strInput.c_str());
        // TODO: input validations.

        return userData;
    }

    // it's a request to send symmetric key.
    if (input == 152){
        userData.messageType = 2;
        printf("Please enter the user name of the client you wish to send key to.\n");
        std::cin.ignore();
        std::getline(std::cin, strInput);
        strcpy(userData.userName,strInput.c_str());
        return userData;
    }

    else{
        printf("The input is incorrect, bye!\n");
        exit(-1);
    }
}
