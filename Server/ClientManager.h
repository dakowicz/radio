//
// Created by erysman on 18.05.16.
//

#ifndef SERVER_CLIENTMANAGER_H
#define SERVER_CLIENTMANAGER_H


#include "Dispatcher.h"
#include "Sender.h"
#include "SocketListener.h"
#include "BlockingMap.h"


class ClientManager {
public:

    ClientManager(Dispatcher* dispatcher, int newSocketDescriptor);

    ~ClientManager();

    void handle(BlockingMap<int, ClientManager*> *blockingMap);

private:

    void deleteClient();

    void log(const char *message) const;

    void registerThread(BlockingMap<int, ClientManager*> *blockingMap);

    void unregisterThread(BlockingMap<int, ClientManager*> *blockingMap);

    SocketListener *socketListener;

    std::thread *socketListnerThread;

    Sender *sender;

    std::thread *senderThread;

    int socketDescriptor;
};


#endif //SERVER_CLIENTMANAGER_H
