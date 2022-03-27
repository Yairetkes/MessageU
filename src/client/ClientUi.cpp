//
// Created by Yair on 19/03/2022.
//

#include "ClientUi.h"

ClientUi::uiData ClientUi::userIntention() {
    int input = -1;
    char *strInput;

    while(input == -1) {
        printf(uiMessage);
        std::cin>>input;
        if(input != -1)
            break;
    }

    userData.reqCode = input;

    std::cout << input << std::endl;
    // TODO: input validations.

    if (input == 110){
        // checking if file me.info exist.
        FILE *file;
        if (!(file = fopen("me.info", "r"))) {
            fclose(file);
            printf(signingMessage);
            std::cin>>strInput;
            while(strlen(strInput) > Max_NAME_LEN){
                printf("The user name entered is too long, please try again.");
                std::cin>>strInput;
            }
            strcpy(userData.userName,strInput);

        } else {// if file me.info exist.
            printf("Error! \nme.info file already exist.");
            exit(-1);
        }

    }
    return userData;
    // TODO: check if cin considered safe (for the report). replace it or write about it...??
    }
