//
// Created by tomasz on 05.05.16.
//


#include <iostream>
#include "SocketListener.h"
#include "Data.h"

SocketListener::SocketListener(int socketDescriptor, Dispatcher *dispatcher) {
    this->socketDescriptor = socketDescriptor;
    this->dispatcher = dispatcher;
}

SocketListener::~SocketListener() {

}

void SocketListener::handle() {
    //TODO blocking on given socket for incoming messages
    while(!isClosed) {
        Data *newMessage = readMessage();
        if(newMessage != nullptr) {
            dispatcher->addMessage(newMessage);
        } else {
            perror("Wrong message\n");
        }
    }
}

Data* SocketListener::readMessage() {

    Header *header = readHeader();

    if(header == nullptr){
        return nullptr;
    }

    uint8_t* data = new uint8_t[header->getLength()];
    int  n = read(socketDescriptor, data, header->getLength());
    if (n < 0) {
        perror("ERROR reading content from socket\n");
    }

    //TODO
    return nullptr;

}

Header* SocketListener::readHeader() {
    uint8_t head[7];
    int  n = read(socketDescriptor,head,7);
    if (n < 0) {
        perror("ERROR reading header from socket\n");
    }else if(n == 0){
        perror("connection finished\n");
        this->isClosed=true;
        return nullptr;
    }
    try {
        Header *header = new Header(head);

        return header;
    }
    catch ( const std::exception& error )
    {
        std::cerr << error.what() << std::endl;
        return nullptr;
    }
}











