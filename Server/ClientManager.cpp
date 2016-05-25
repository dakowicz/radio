//
// Created by erysman on 18.05.16.
//
#include <iostream>
#include "ClientManager.h"


ClientManager::ClientManager(Dispatcher *dispatcher, int newSocketDescriptor) {
    this->socketDescriptor = newSocketDescriptor;
    this->socketListener = new SocketListener(newSocketDescriptor, dispatcher);
    this->sender = new Sender(newSocketDescriptor);
}

ClientManager::~ClientManager() {
    delete this->socketListener;
    delete this->sender;
    delete this->socketListnerThread;
    delete this->senderThread;
}

void ClientManager::handle() {

    log("Created new ClientManager on socket: " + socketDescriptor);

    this->socketListnerThread = new std::thread(&SocketListener::handle, this->socketListener);
    log("Created new SocketListener on socket: " + socketDescriptor);

    this->senderThread = new std::thread(&Sender::handle, this->sender);
    log("Created new Sender on socket: " + socketDescriptor);

    socketListnerThread->join();
    senderThread->join();

    deleteClient();
    log("Socket has been closed: " + socketDescriptor);
}

void ClientManager::log(const char *message) const { std::cout << message << std::endl; }

void ClientManager::deleteClient() {
    close(this->socketDescriptor);
}

