//
// Created by tomasz on 25.05.16.
//

#ifndef SERVER_TCPLISTENER_H
#define SERVER_TCPLISTENER_H

#include <cstdio>
#include <unistd.h>
#include <cstring>
#include <atomic>

#include <string>
#include <atomic>
#include <shared_mutex>
#include "Data.h"

class TCPListener {
public:

    TCPListener(int socketDescriptor);

    ~TCPListener();

    Data *readMessage();

    /*unsigned char *readN(int num);

    void setReady();*/

private:

    int socketDescriptor;

    Header *header;
/*
    int collectedBytes; //actual number of read bytes

    unsigned char *messageBuffer;

    bool headerReady;*/

    static std::string MODULE_NAME;
/*
    void readHeader();

    bool isUnavailable(int err) const;

    bool wouldBlock(int err) const;

    void checkReadError(int err) const;

    void copyReadData(char *messagePortion, int n);

    bool isMessageComplete(int totalBytesNumber) const;*/

    void readMessageContent();

    void readHeader();

    int bytesToRead;

    int bytesAlreadyRead;

    bool isHeaderComplete;

    char *headerBuffer;

    char *contentBuffer;

    void checkIfHeaderComplete();

    void checkIfMessageComplete();

    bool isReadingComplete() const;

    bool isMessageComplete;

    Data *getMessage() const;

    void readBytes(char *buffer);

    void updatePayload(int payload);

    bool isReadSuccessful(int payload) const;

    bool hasConnectionBeenClosed(int payload) const;

    void closeConnection();

    bool isConnectionClosed;

    void checkErrorCode(int payload);

    void log(std::string message);

    void resetHeader();

    void resetHeaderBuffer();
};


#endif //SERVER_TCPLISTENER_H
