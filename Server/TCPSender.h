//
// Created by tomasz on 24.05.16.
//

#ifndef SERVER_TCPSENDER_H
#define SERVER_TCPSENDER_H

#include <string>
#include <fstream>
#include <cstring>
#include <unistd.h>
#include "Logger.h"


class TCPSender {
public:

    TCPSender(int socketDescriptor) : socketDescriptor(socketDescriptor), logger(MODULE_NAME, socketDescriptor) {
        std::string fileName = std::string("/home/tomasz/prog/radio/Server/") + std::string("newfile") + std::to_string(socketDescriptor);
        this->file = new std::ofstream(fileName);
    }

    ~TCPSender() {
        delete file;
    }

    void sendMusic(char *message, int messageSize)const;

    void sendVotes(char *message, int messageSize)const;

    void sendConnectionInfo(char *message, int messageSize)const;

private:

    int socketDescriptor;

    Logger logger;

    static std::string MODULE_NAME;

    void send(char *header, char *message, int messageSize)const;

    void addHeader(char *header, char *dataToSend);

    std::ofstream *file;

    void writeData(char *dataToSend, int dataToSendSize) const;

    void addMessage(char *message, char *dataToSend, int messageSize) const;

    int pointerPosition;
};


#endif //SERVER_TCPSENDER_H
