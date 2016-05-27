//
// Created by tomasz on 25.05.16.
//

#ifndef SERVER_TCPLISTENER_H
#define SERVER_TCPLISTENER_H

#include <string>
#include "Data.h"

class TCPListener {
public:

    TCPListener(int socketDescriptor);

    ~TCPListener();

    Data *readMessage();

private:

    int socketDescriptor;

    int bytesToRead;

    static std::string MODULE_NAME;
};


#endif //SERVER_TCPLISTENER_H
