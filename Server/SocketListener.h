//
// Created by tomasz on 05.05.16.
//

#ifndef SERVER_SOCKETLISTENER_H
#define SERVER_SOCKETLISTENER_H


#include "Data.h"
#include "TCPListener.h"
#include "Dispatcher.h"
#include <unistd.h>

class Dispatcher;

class SocketListener {
public:

    SocketListener(const std::shared_ptr<Dispatcher> &dispatcher, int newSocketDescriptor);

    ~SocketListener();

    void handle();

    bool isRunning() const { return running; }

    void setRunning(bool running) { this->running = running; }

private:

    void log(std::string message);

    bool running;

    int socketDescriptor;

    std::shared_ptr<Dispatcher> dispatcher;

    std::shared_ptr<TCPListener> tcpListener;

    static std::string MODULE_NAME;
};

#endif //SERVER_SOCKETLISTENER_H
