//
//  main.cpp
//
//  Created by Johnathan Chiu on 2/21/19.
//  Copyright © 2019 Johnathan Chiu. All rights reserved.
//

#include <iostream>
#include "socket.hpp"

using namespace std;
using namespace serversock;

struct serversock::objectData myData;

int main(int argc, char *argv[]) {
    objectData *pointer = &myData;
    serversock::createConnection();
    //while (1 == 1) {
        long i = 1000000;
    while (i>0){
        i--;
        std::cout << i;
        std::cout << "\n";
    }
    serversock::readValues(pointer);
    //}
    return 0;
}