//
// Created by tomasz on 24.05.16.
//

#ifndef SERVER_TCPSENDER_H
#define SERVER_TCPSENDER_H

#include <string>
#include <fstream>
#include <cstring>
#include <unistd.h>
#include <atomic>
#include "Logger.h"


class TCPSender {
public:

    TCPSender(int socketDescriptor) : socketDescriptor(socketDescriptor), logger(MODULE_NAME, socketDescriptor) {
//        std::string fileName = std::string("/home/tomasz/prog/radio/Server/") + std::string("newfile") + std::to_string(socketDescriptor);
//        this->file = new std::ofstream(fileName);
    }

    ~TCPSender() {
//        delete file;
    }

    void sendMusic(char *message, int messageSize);

    void sendVotes(char *message, int messageSize);

    void sendConnectionInfo(char *message, int messageSize);

    bool isConnectionClosed();

    void setConnectionClosed();

private:

    int socketDescriptor;

    Logger logger;

    static std::string MODULE_NAME;

    void sendMessage(char *header, char *message, int messageSize);

//    std::ofstream *file;

    void writeData(char *dataToSend, int dataToSendSize);

    std::atomic<bool> connectionClosed;

    void sendN(const char *dataToSend, int dataToSendSize);

    bool isClosedByRemote(int bytesSent) const;
};


#endif //SERVER_TCPSENDER_H
