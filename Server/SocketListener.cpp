//
// Created by tomasz on 05.05.16.
//


#include "SocketListener.h"

SocketListener::SocketListener(int socketDescriptor, Dispatcher *dispatcher) {
    this->socketDescriptor = socketDescriptor;
    this->dispatcher = dispatcher;
    this->tcpListener = new TCPListener(socketDescriptor);
}

SocketListener::~SocketListener() {

}

void SocketListener::handle() {
    while(!running) {
        Data *newMessage = tcpListener->readMessage();
        if(newMessage != nullptr) {
            dispatcher->addMessage(newMessage);
        }
    }
}

void SocketListener::read() {
    this->tcpListener->SetReady();
}











