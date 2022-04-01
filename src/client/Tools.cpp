//
// Created by Yair on 20/03/2022.
//

#include "Tools.h"

std::string Tools::readIntoStr( std::string fileName){

    std::string cwdPath = "C:\\Users\\Yair\\source\\repos\\MessageU\\src\\client\\";
    std::string fullPathFile = cwdPath.append(fileName);
    std::ifstream file;
    file.open(fullPathFile, std::ios::in);

    // TODO: super impoetant: send to Matanya my project with the next 2 lines undocumented (and document
    //  the above 4 lines). is should work on matanyas pc (but in my pc it wont work (idk why)).

//    std::ifstream file;
//    file.open(fileName, std::ios::in);

    if (!file.is_open()) {
        throw "File " + fileName + " is not found. make sure file exists...";
    }

    std::streampos fsize = 0;
    fsize = file.tellg();
    file.seekg(0, std::ios::end);
    fsize = file.tellg() - fsize;
    file.seekg(0);
    size_t fileSize = fsize;

//    size_t fileSize = 13;
    char* buffer = new char[fileSize];
    file.read(buffer, fileSize);
    file.close();
    std::string data(buffer, fileSize);
    delete[] buffer;

    printf(data.c_str());

    return data;
}

Tools::serverInfo Tools::readServerInfo(){
    // continue debugging from here
    std::string data = Tools::readIntoStr( SERVER_INFO_FILE_NAME);

    std::string delimiter = ":";
    std::string ip = data.substr(0, data.find(delimiter));
    std::string host = data.substr(ip.length() + 1);

    serInfo.host = host;
    serInfo.ip = ip;

    return serInfo;
}



//int Tools::strcpy_s(int *d, unsigned long dmax, const int *s) {
//        if(dmax<=1||!d){
//            if(!d||!dmax)
//                return 22;
//            *d=C(0);
//            return 0;
//        }
//        for(C*de=d+dmax-1;
//            (d!=de||(*d=C(0)))&&(*d=*s);
//            ++d,++s);
//        return 0;
//}
