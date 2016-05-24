//
// Created by erysman on 18.05.16.
//
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
    this->socketListnerThread = new std::thread(&SocketListener::handle, this->socketListener);
    this->senderThread = new std::thread(&Sender::handle, this->sender);

    socketListnerThread->join();
    senderThread->join();

    deleteClient();
}

void ClientManager::handleSocketListener(SocketListener *socketListener) {
    socketListener->handle();
}

void ClientManager::handleSender(Sender *sender) {
    sender->handle();
}

void ClientManager::deleteClient() {
    close(this->socketDescriptor);
}













