//
// Created by erysman on 18.05.16.
//

#ifndef SERVER_CLIENTMANAGER_H
#define SERVER_CLIENTMANAGER_H


#include <thread>
#include "Sender.h"
#include "SocketListener.h"
#include "AtomicMap.h"

class ClientManager {
public:

    ClientManager(Dispatcher &dispatcher, int newSocketDescriptor) : socketDescriptor(newSocketDescriptor), socketListener(dispatcher, newSocketDescriptor),
            sender(newSocketDescriptor), logger(MODULE_NAME, newSocketDescriptor) {}
    ~ClientManager(){
        logger.log("destructor");
    }

    void handle(const std::shared_ptr<AtomicMap<int, ClientManager *>> &blockingMap);

    void send(Data *data);

    int getSocketDescriptor() const { return socketDescriptor; }

    void addReadRequest();

    void setNoReadRequests();

    bool operator==(ClientManager &clientManager) const;

private:

    SocketListener socketListener;

    Sender sender;

    Logger logger;

    int socketDescriptor;

    static std::string MODULE_NAME;

    void deleteClient();

    void registerThread(const std::shared_ptr<AtomicMap<int, ClientManager *>> &blockingMap);

    void unregisterThread(const std::shared_ptr<AtomicMap<int, ClientManager *>> &blockingMap);
};


#endif //SERVER_CLIENTMANAGER_H
