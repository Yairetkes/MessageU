//
// Created by Yair on 19/03/2022.
//

#include "ClientUi.h"

int ClientUi::userIntention() {
    int input = -1;

    while(input == -1) {
        printf(uiMessage);
        std::cin>>input;
        if(input != -1)
            break;
    }

    std::cout << input << std::endl;
    // TODO: input validations.
    return input;
    // TODO: check if cin considered safe (for the report). replace it or write about it...??
    return 1;
}
