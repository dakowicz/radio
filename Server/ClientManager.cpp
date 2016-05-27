//
// Created by erysman on 18.05.16.
//
#include <iostream>
#include "ClientManager.h"

std::string ClientManager::MODULE_NAME = "ClientManager";

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
    this->senderThread = new std::thread(&Sender::handle, this->sender);

    sender->addMessage(new Data(DataType::STREAM, new unsigned char (10)));

    socketListnerThread->join();
    senderThread->join();

    deleteClient();
    unregisterThread(blockingMap);
}

void ClientManager::deleteClient() {
    close(this->socketDescriptor);
    log("Socket has been closed");
}

void ClientManager::registerThread(BlockingMap<int, ClientManager*>  *blockingMap) {
    blockingMap->insert(socketDescriptor, this);
    log("Registered");
}

void ClientManager::unregisterThread(BlockingMap<int, ClientManager*>  *blockingMap) {
    blockingMap->erase(socketDescriptor, this);
    log("Unregistered");
}

void ClientManager::log(std::string message) const {
    std::cout << MODULE_NAME << this->socketDescriptor << ": " << message << std::endl << std::flush;
}