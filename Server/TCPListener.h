//
// Created by tomasz on 25.05.16.
//

#ifndef SERVER_TCPLISTENER_H
#define SERVER_TCPLISTENER_H

#include <cstdio>
#include <unistd.h>
#include <cstring>
#include <atomic>
#include "Data.h"
#include "Header.h"

class TCPListener {

public:
    TCPListener(int socketDescriptor);
    ~TCPListener();

    Data *readMessage();
    unsigned char *readN(int num);
    void SetReady();

private:
    int socketDescriptor;
    int collectedBytes; //actual number of read bytes
    unsigned char *messageBuffer;
    Header *header;

    bool headerReady;
    std::atomic<bool> readyToRead;

    void readHeader();
};


#endif //SERVER_TCPLISTENER_H
