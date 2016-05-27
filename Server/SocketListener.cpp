//
// Created by tomasz on 05.05.16.
//


#include "SocketListener.h"

std::string SocketListener::MODULE_NAME = "SocketListener";

SocketListener::SocketListener(int socketDescriptor, Dispatcher *dispatcher) {
    this->socketDescriptor = socketDescriptor;
    this->dispatcher = dispatcher;
    this->tcpListener = new TCPListener(socketDescriptor);
}

SocketListener::~SocketListener() {
}

void SocketListener::handle() {
    this->running = true;
    while(running) {
        Data *newMessage = tcpListener->readMessage();
        dispatcher->addMessage(newMessage);
    }
}

void SocketListener::log(std::string message) {
    std::cout << MODULE_NAME << this->socketDescriptor << ": " <<  message << std::endl << std::flush;
}