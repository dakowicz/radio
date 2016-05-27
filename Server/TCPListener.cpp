//
// Created by tomasz on 25.05.16.
//

#include <iostream>
#include <memory>
#include "TCPListener.h"

std::string TCPListener::MODULE_NAME = "TCPListener";

TCPListener::TCPListener(int socketDescriptor) {
    this->socketDescriptor = socketDescriptor;
}

TCPListener::~TCPListener() {
}

Data * TCPListener::readMessage() {
    return nullptr;
}


Data *readMessage() {
    return nullptr;
}

