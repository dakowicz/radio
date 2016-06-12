//
// Created by erysman on 18.05.16.
//
#include "ClientManager.h"

std::string ClientManager::MODULE_NAME = "ClientManager";

void ClientManager::handle(const std::shared_ptr<AtomicMap <int, ClientManager *>> &blockingMap) {
    registerThread(blockingMap);
    logger.log("Created");

    std::thread socketListenerThread(&SocketListener::handle, &socketListener);
    std::thread senderThread(&Sender::handle, &sender);

    socketListenerThread.join();
    sender.setConnectionClosed(true);
    senderThread.join();

    deleteClient();
    unregisterThread(blockingMap);
}

void ClientManager::deleteClient() {
    close(this->socketDescriptor);
    logger.log("Socket has been closed");
}

void ClientManager::registerThread(const std::shared_ptr<AtomicMap<int, ClientManager *>> &blockingMap) {
    blockingMap->insert(socketDescriptor, this);
}

void ClientManager::unregisterThread(const std::shared_ptr<AtomicMap<int, ClientManager *>> &blockingMap) {
    blockingMap->erase(socketDescriptor, this);
}

void ClientManager::send(Data *data) {
    sender.addMessage(data);
}

void ClientManager::addReadRequest() {
    socketListener.addReadRequest();
}

void ClientManager::setNoReadRequests() {
    socketListener.resetReadReaquestCounter();
}

bool ClientManager::operator==(ClientManager &clientManager) const {
    return this == &clientManager;
}