//
// Created by tomasz on 05.05.16.
//

#ifndef SERVER_SOCKETLISTENER_H
#define SERVER_SOCKETLISTENER_H


#include "Data.h"
#include "TCPListener.h"
#include "Dispatcher.h"
#include <unistd.h>
#include <atomic>

class Dispatcher;

class SocketListener {
public:

    SocketListener(const std::shared_ptr<Dispatcher> &dispatcher, int newSocketDescriptor);

    ~SocketListener();

    void handle();

    const bool isRunning() const { return running.load(); }

    void setRunning(bool val) { this->running = val; }

private:

    void log(std::string message);

    std::atomic<bool> running;

    int socketDescriptor;

    std::shared_ptr<Dispatcher> dispatcher;

    std::shared_ptr<TCPListener> tcpListener;

    static std::string MODULE_NAME;
};

#endif //SERVER_SOCKETLISTENER_H
