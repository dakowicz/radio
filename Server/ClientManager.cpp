//
// Created by erysman on 18.05.16.
//
#include <iostream>
#include "ClientManager.h"

std::string ClientManager::MODULE_NAME = "ClientManager";

ClientManager::ClientManager(const std::shared_ptr<Dispatcher> &dispatcher, int newSocketDescriptor) {
    this->socketDescriptor = newSocketDescriptor;
    this->socketListener = new SocketListener(dispatcher, newSocketDescriptor);
    this->sender = new Sender(newSocketDescriptor);
    this->logger = new Logger(MODULE_NAME, socketDescriptor);
}

ClientManager::~ClientManager() {
    delete socketListener;
    delete sender;
    delete logger;
}

void ClientManager::handle(const std::shared_ptr<AtomicMap <int, ClientManager *>> &blockingMap) {
    registerThread(blockingMap);
    logger->log("Created");

    std::thread socketListnerThread(&SocketListener::handle, this->socketListener);
    std::thread senderThread(&Sender::handle, this->sender);

    socketListnerThread.join();
    senderThread.join();

    deleteClient();
    unregisterThread(blockingMap);
}

void ClientManager::deleteClient() {
    close(this->socketDescriptor);
    logger->log("Socket has been closed");
}

void ClientManager::registerThread(const std::shared_ptr<AtomicMap<int, ClientManager *>> &blockingMap) {
    blockingMap->insert(socketDescriptor, this);
}

void ClientManager::unregisterThread(const std::shared_ptr<AtomicMap<int, ClientManager *>> &blockingMap) {
    blockingMap->erase(socketDescriptor, this);
}

void ClientManager::send(Data *data) {
    this->sender->addMessage(data);
}

void ClientManager::addReadRequest() {
    this->socketListener->addReadRequest();
}

void ClientManager::setNoReadRequests() {
    this->socketListener->resetReadReaquestCounter();
}




