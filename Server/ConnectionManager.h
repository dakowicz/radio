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
#include "AtomicMap.h"


class ConnectionManager {
public:

    ConnectionManager(const std::shared_ptr<Dispatcher> &dispatcher, int port,
                          const std::shared_ptr<AtomicMap<int, ClientManager*>> &clients);

    ~ConnectionManager();

    void start();

private:

    void initConfig(int &sockfd, sockaddr_in &serv_addr, sockaddr_in &cli_addr);

    void addClient(int newSocketDescriptor);

    void handleError(const char *errorMessage) const;

    int port;

    int socketDescriptor;

    std::shared_ptr<Dispatcher> dispatcher;

    std::shared_ptr<AtomicMap<int, ClientManager*>> clients;

    bool running;

    static std::string MODULE_NAME;

    static int QUEUE_LIMIT;
};


#endif //SERVER_CONNECTIONMANAGER_H
