//
// Created by tomasz on 05.05.16.
//

#include "SocketListener.h"

SocketListener::SocketListener(int socketDescriptor) {
    this->socketDescriptor = socketDescriptor;
}

SocketListener::~SocketListener() {

}

void SocketListener::handle() {
    //TODO blocking on given socket for incoming messages
}





