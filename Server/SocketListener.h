//
// Created by tomasz on 05.05.16.
//

#ifndef SERVER_SOCKETLISTENER_H
#define SERVER_SOCKETLISTENER_H


#include <unistd.h>
#include "TCPListener.h"
#include "Dispatcher.h"


class SocketListener {
public:

    SocketListener(Dispatcher &dispatcher, int newSocketDescriptor) :
            dispatcher(dispatcher), tcpListener(newSocketDescriptor), socketDescriptor(newSocketDescriptor), logger(MODULE_NAME, newSocketDescriptor) {};

    void handle();

    void addReadRequest();

    void resetReadReaquestCounter();

private:

    int socketDescriptor;

    Dispatcher &dispatcher;

    TCPListener tcpListener;

    Logger logger;

    int readRequestsCounter;

    std::mutex mutex;

    std::condition_variable cond;

    static std::string MODULE_NAME;

    void waitForRequest();

    Data *readMessage();

    bool isConnectionClosed();
};

#endif //SERVER_SOCKETLISTENER_H
