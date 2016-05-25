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

class ConnectionManager {

public:
    ConnectionManager(Dispatcher *dispatcher, int port);
    ~ConnectionManager();
    void start();

    static int QUEUE_LIMIT;

private:
    int port;
    int socketDescriptor;
    Dispatcher *dispatcher;
    std::map<int, std::thread*> clientThreads;
    std::vector<int> clientSockets;

    void initConfig(int &sockfd, sockaddr_in &serv_addr, sockaddr_in &cli_addr);

    void addClient(int newSocketDescriptor);

    void static handleClient(int newSocketDescriptor, Dispatcher *dispatcher);

    void handleError(const char *errorMessage) const;
};


#endif //SERVER_CONNECTIONMANAGER_H
