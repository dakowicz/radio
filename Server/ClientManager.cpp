//
// Created by erysman on 18.05.16.
//
#include <iostream>
#include "ClientManager.h"

std::string ClientManager::MODULE_NAME = "ClientManager";

ClientManager::ClientManager(const std::shared_ptr<Dispatcher> &dispatcher, int newSocketDescriptor) {
    this->socketDescriptor = newSocketDescriptor;
    this->socketListener = std::make_shared<SocketListener>(dispatcher, newSocketDescriptor);
    this->sender = std::make_shared<Sender>(newSocketDescriptor);
}

ClientManager::~ClientManager() {
}

void ClientManager::handle(const std::shared_ptr<AtomicMap <int, ClientManager*>> &blockingMap) {
    registerThread(blockingMap);
    log("Created");

    std::thread socketListnerThread(&SocketListener::handle, this->socketListener.get());
    std::thread senderThread(&Sender::handle, this->sender.get());

    socketListnerThread.join();
    senderThread.join();

    deleteClient();
    unregisterThread(blockingMap);
}

void ClientManager::deleteClient() {
    close(this->socketDescriptor);
    log("Socket has been closed");
}

void ClientManager::registerThread(const std::shared_ptr<AtomicMap<int, ClientManager *>> &blockingMap) {
    blockingMap->insert(socketDescriptor, this);
}

void ClientManager::unregisterThread(const std::shared_ptr<AtomicMap<int, ClientManager *>> &blockingMap) {
    blockingMap->erase(socketDescriptor, this);
}

void ClientManager::log(std::string message) const {
    std::cout << MODULE_NAME << this->socketDescriptor << ": " << message << std::endl << std::flush;
}

void ClientManager::send(Data* data) {
    this->sender->addMessage(data);
}

