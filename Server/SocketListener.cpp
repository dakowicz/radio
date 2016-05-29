//
// Created by tomasz on 05.05.16.
//


#include "SocketListener.h"

std::string SocketListener::MODULE_NAME = "SocketListener";

SocketListener::SocketListener(const std::shared_ptr<Dispatcher> &dispatcher, int newSocketDescriptor) {
    this->tcpListener = new TCPListener(socketDescriptor);
    this->dispatcher = dispatcher;
    this->socketDescriptor = socketDescriptor;
}


SocketListener::~SocketListener() {
    delete tcpListener;
}

void SocketListener::handle() {
    this->running = true;
    while(isRunning()) {
        Data *newMessage = tcpListener->readMessage();
        dispatcher->addMessage(newMessage);
    }
}

void SocketListener::log(std::string message) {
    std::cout << MODULE_NAME << this->socketDescriptor << ": " <<  message << std::endl << std::flush;
}

