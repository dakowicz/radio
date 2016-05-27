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

    bool isRunning() const { return running; }

    void setRunning(bool running) { this->running = running; }

private:

    void log(std::string message);

    bool running;

    int socketDescriptor;

    Dispatcher *dispatcher;

    TCPListener *tcpListener;

    static std::string MODULE_NAME;
};

#endif //SERVER_SOCKETLISTENER_H
