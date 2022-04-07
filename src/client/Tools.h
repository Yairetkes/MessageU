//
// Created by Yair on 20/03/2022.
//

#ifndef UNTITLED_TOOLS_H
#define UNTITLED_TOOLS_H

#include<fstream>
#include <sstream>
#include<iostream>
#include<iterator>
#include <string>

//#define SERVER_INFO_FILE_NAME "server.info"
const std::string SERVER_INFO_FILE_NAME = "server.info";
const std::string CLIENT_INFO_FILE_NAME = "me.info";

class Tools {
public:

    struct serverInfo{
        std::string ip;
        std::string host;
    }serInfo;

    struct meInfo{
        std::string clientName;
        std::string clientID;
        std::string privateKey; // TODO: should be string or some encrypting type??
        std::string publicKey;
    }myInfo;

    // this method reads data from file to string
    std::string readIntoStr( std::string fileName);

    // this method read the information of server from file (ip and port).
    serverInfo readServerInfo();

    meInfo readClientInfo();

    unsigned char* Tools::strToHexStr(std::string hexStr);

    const char* Tools::hexStrToStr(const unsigned char* binArray, size_t arrSize);

    int Tools::writeToFile(const std::string& fName, const std::string& dataTofile);

    // strcpy is an unsafe function, so I had to add this function, which block the option
    // of buffer overflow.
//    int strcpy_s(C*d,unsigned long dmax,const C*s);

};


#endif //UNTITLED_TOOLS_H
