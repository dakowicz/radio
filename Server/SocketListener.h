//
// Created by tomasz on 05.05.16.
//

#ifndef SERVER_SOCKETLISTENER_H
#define SERVER_SOCKETLISTENER_H


#include "Dispatcher.h"
#include "MessageDTO.h"
#include <unistd.h>


class SocketListener {

public:
    SocketListener(int socketDescriptor, Dispatcher *dispatcher);
    ~SocketListener();
    void handle();

private:
    bool isClosed;
    int socketDescriptor;
    Dispatcher *dispatcher;
    MessageDTO *readMessage();

    Header *readHeader();
};

#endif //SERVER_SOCKETLISTENER_H
