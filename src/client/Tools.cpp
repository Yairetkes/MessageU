//
// Created by Yair on 20/03/2022.
//

#include "Tools.h"

std::string Tools::readIntoStr( std::string fileName){

    std::string cwdPath = "C:\\Users\\Yair\\source\\repos\\MessageU\\src\\client\\";
    std::string fullPathFile = cwdPath.append(fileName);
    std::ifstream file;
    file.open(fullPathFile, std::ios::in);

    // TODO: super important: send to Matanya my project with the next 2 lines undocumented (and document
    //  the above 4 lines). it should work on Matanyas pc (but in my pc it wont work (idk why, for some reason
    //  it requires the pull path)).

//    std::ifstream file; // TODO: dont erase!!!
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

    return std::string(data.c_str());
}


Tools::serverInfo Tools::readServerInfo(){
    std::string data = Tools::readIntoStr( SERVER_INFO_FILE_NAME);

    std::string delimiter = ":";
    std::string ip = data.substr(0, data.find(delimiter));
    std::string host = data.substr(ip.length() + 1);

    serInfo.host = host;
    serInfo.ip = ip;

    return serInfo;
}

Tools::meInfo Tools::readClientInfo() {
    std::string data = Tools::readIntoStr( CLIENT_INFO_FILE_NAME);

    std::string delimiter = "\n";
    myInfo.clientName = data.substr(0, data.find(delimiter));
    data = data.substr(myInfo.clientName.length() + 1);
    myInfo.clientID = data.substr(0, data.find(delimiter));
    myInfo.privateKey = data.substr( myInfo.clientID.length() + 1);

    return myInfo;

}

unsigned char* Tools::strToHexStr(std::string hexaStr) {
    int n;
    unsigned char* resStr = new unsigned char[hexaStr.length() / 2];
    std::string couple;
    for (size_t i = 0; i < hexaStr.length() - 1; i += 2) {
        couple = hexaStr.substr(i, 2);
        std::stringstream ss(couple);
        ss >> std::hex >> n;


        resStr[i / 2] = n;
    }


    return resStr;
}


const char* Tools::hexStrToStr(const unsigned char* hexArray, size_t arraySize)
{
    static char syms[] = "0123456789ABCDEF";

    std::stringstream ss;
    for (size_t i = 0; i < arraySize; i++) {
        ss << syms[((hexArray[i] >> 4) & 0xf)] << syms[hexArray[i] & 0xf];
    }
    return ss.str().c_str();
}

// TODO: probably need to pass file name as full path!! test it
int Tools::writeToFile(const std::string& fName, const std::string& dataTofile)
{
    std::ofstream file;
    file.open(fName);
    if (!file.is_open())
        return 1;
    file << dataTofile;
    file.close();
    return 0;
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
