//
// Created by erysman on 18.05.16.
//

#ifndef SERVER_CLIENTMANAGER_H
#define SERVER_CLIENTMANAGER_H

#include <thread>
#include "../sender/Sender.h"
#include "../receiver/SocketListener.h"
#include "domain/ClientsMap.h"

class Dispatcher;

class SocketListener;

class ClientManager {
public:

    ClientManager(Dispatcher *dispatcher, int newSocketDescriptor);

    ~ClientManager();

    void handle(const std::shared_ptr<ClientsMap<int, ClientManager *>> &blockingMap);

    int getSocketDescriptor() const { return socketDescriptor; }

    void addReadRequest();

    void setNoReadRequests();

    bool operator==(ClientManager &clientManager) const;

    void send(std::shared_ptr<Data> data);

private:

    SocketListener *socketListener;

    Sender *sender;

    Logger *logger;

    int socketDescriptor;

    static std::string MODULE_NAME;

    void deleteClient();

    void registerThread(const std::shared_ptr<ClientsMap<int, ClientManager *>> &blockingMap);

    void unregisterThread(const std::shared_ptr<ClientsMap<int, ClientManager *>> &blockingMap);
};


#endif //SERVER_CLIENTMANAGER_H
