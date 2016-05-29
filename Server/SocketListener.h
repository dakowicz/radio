//
// Created by tomasz on 05.05.16.
//

#ifndef SERVER_SOCKETLISTENER_H
#define SERVER_SOCKETLISTENER_H


#include "Dispatcher.h"
#include "Data.h"
#include "TCPListener.h"
#include <unistd.h>


class SocketListener {

public:
    SocketListener(int socketDescriptor, Dispatcher *dispatcher);
    ~SocketListener();
    void handle();

    void read();

    bool isRunning() const { return running; }
    void setRunning(bool running) { SocketListener::running = running; }

private:
    bool running;
    int socketDescriptor;
    Dispatcher *dispatcher;
    TCPListener *tcpListener;
};

#endif //SERVER_SOCKETLISTENER_H
