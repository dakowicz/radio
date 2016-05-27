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

void ClientManager::handle(BlockingMap<int, ClientManager*> * blockingMap) {
    registerThread(blockingMap);

    this->socketListnerThread = new std::thread(&SocketListener::handle, this->socketListener);
    log("New SocketListener on socket: " + socketDescriptor);

    this->senderThread = new std::thread(&Sender::handle, this->sender);
    log("New Sender on socket: " + socketDescriptor);

    sender->addMessage(new Data(DataType::STREAM, new unsigned char(10)));

    socketListnerThread->join();
    senderThread->join();

    deleteClient();
    log("Socket has been closed: " + socketDescriptor);
    unregisterThread(blockingMap);
}

void ClientManager::log(const char *message) const {
    std::cout << "ClientManager: " << message << std::endl << std::flush;
}

void ClientManager::deleteClient() {
    close(this->socketDescriptor);
}

void ClientManager::registerThread(BlockingMap<int, ClientManager*>  *blockingMap) {
    blockingMap->insert(socketDescriptor, this);
}

void ClientManager::unregisterThread(BlockingMap<int, ClientManager*>  *blockingMap) {
    blockingMap->erase(socketDescriptor, this);
}





