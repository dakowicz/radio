//
// Created by tomasz on 05.05.16.
//

#ifndef SERVER_CONNECTIONMANAGER_H
#define SERVER_CONNECTIONMANAGER_H


#include <vector>
#include <thread>
#include <netinet/in.h>
#include <map>
#include "Dispatcher.h"
#include "SocketListener.h"
#include "Sender.h"
#include "ClientManager.h"
#include "BlockingMap.h"

class ConnectionManager {
public:

    ConnectionManager(Dispatcher *dispatcher, int port);

    ~ConnectionManager();

    void start();

private:

    void initConfig(int &sockfd, sockaddr_in &serv_addr, sockaddr_in &cli_addr);

    void addClient(int newSocketDescriptor);

    void handleError(const char *errorMessage) const;

    int port;

    int socketDescriptor;

    Dispatcher *dispatcher;

    BlockingMap<int, ClientManager*> *clientThreads;

    bool running;

    static std::string MODULE_NAME;

    static int QUEUE_LIMIT;
};


#endif //SERVER_CONNECTIONMANAGER_H
