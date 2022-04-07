//
// Created by Yair on 19/03/2022.
//

#include "ClientUi.h"

ClientUi::uiData ClientUi::userIntention() {
    int input = -1;
    unsigned int idInput = 0;
    std::string strInput;

    Tools tools = Tools();

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
        std::string cwdPath = "C:\\Users\\Yair\\source\\repos\\MessageU\\src\\client\\";
        std::string fullPathFile = cwdPath.append(FILE_NAME);
        std::ifstream file;
        file.open(fullPathFile, std::ios::in);

        // TODO: super important: send to Matanya my project with the next 2 lines undocumented (and document
        //  the above 4 lines). it should work on Matanyas pc (but in my pc it wont work (idk why, for some reason
        //  it requires the full path)).

//      std::ifstream file; // TODO: dont erase!!!
//      file.open(FILE_NAME, std::ios::in);

        //std::ifstream file(FILE_NAME.c_str());// TODO: dont erase!!!
        // TODO: check if file exist. this check seem to not work, maybe becuse I didnt supply full path of file??
         if (!file.is_open()) {
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
            file.close();
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

        std::getline(std::cin, strInput); // original

        // memcpy_s(userData.userId, 16,hex((uint8_t*)arr, sizeof(strInput) ), 16);
        memcpy_s(userData.userId, 16, tools.strToHexStr(strInput), 16);
        // strcpy(userData.userId,tools.strToHexStr( strInput)); // original

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
