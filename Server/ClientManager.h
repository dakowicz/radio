//
// Created by erysman on 18.05.16.
//

#ifndef SERVER_CLIENTMANAGER_H
#define SERVER_CLIENTMANAGER_H


#include "Dispatcher.h"

#include "Sender.h"
#include "SocketListener.h"

class ClientManager {
public:
    ClientManager(Dispatcher* dispatcher, int newSocketDescriptor);
    ~ClientManager();

    void handle();

private:

    SocketListener *socketListener;
    std::thread *socketListnerThread;

    Sender *sender;
    std::thread *senderThread;

    int socketDescriptor;

    void static handleSocketListener(SocketListener *socketListener);

    void static handleSender(Sender *sender);

    void deleteClient();
};


#endif //SERVER_CLIENTMANAGER_H
