//
// Created by tomasz on 05.05.16.
//

#ifndef SERVER_CONNECTIONMANAGER_H
#define SERVER_CONNECTIONMANAGER_H


#include <vector>
#include <thread>
#include <netinet/in.h>
#include "Dispatcher.h"
#include "SocketListener.h"
#include "Sender.h"

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
    std::vector<SocketListener*> socketListeners;
    std::vector<Sender*> senders;
    std::vector<std::thread*> sendersThreads;

    std::vector<std::thread*> listenersThreads;

    void initConfig(int &sockfd, sockaddr_in &serv_addr, sockaddr_in &cli_addr);

    void handleClient(int newSocketDescriptor);

    void static handleNewSender(int socketDescriptor, Sender *sender);

    void static handleNewSocketListener(int socketDescriptor, SocketListener *socketListener);

    void configureSocketListener(int newSocketDescriptor);

    void configureSender(int newSocketDescriptor);

    void handleError(const std::string) const;
};


#endif //SERVER_CONNECTIONMANAGER_H
