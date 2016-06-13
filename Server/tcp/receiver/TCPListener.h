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
#include "../../service/dispatcher/domain/Data.h"
#include "../../logger/Logger.h"


class TCPListener {
public:

    TCPListener(int socketDescriptor) :
            socketDescriptor(socketDescriptor), logger(MODULE_NAME, socketDescriptor), isHeaderComplete(false), isMessageComplete(false),
            bytesAlreadyRead(0), bytesToRead(0), header(nullptr), contentBuffer(nullptr), headerBuffer() {}

    std::shared_ptr<Data> readMessage();

    const bool isConnectionsClosed() const { return connectionClosed.load(); }

private:

    int socketDescriptor;

    Header *header;

    static std::string MODULE_NAME;

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

    std::shared_ptr<Data> getMessage() const;

    void readBytes(char *buffer);

    void updatePayload(int payload);

    bool isReadSuccessful(int payload) const;

    bool connectionHasBeenClosed(int payload) const;

    void closeConnection();

    std::atomic<bool>connectionClosed;

    void checkErrorCode(int payload);

    void resetHeader();

    void resetHeaderBuffer();

    Logger logger;
};


#endif //SERVER_TCPLISTENER_H
