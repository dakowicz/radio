//
// Created by tomasz on 05.05.16.
//

#include <unistd.h>
#include <cstring>
#include "Sender.h"
#include "Header.h"


Sender::Sender(int socketDescriptor) {
    this->socketDescriptor = socketDescriptor;
    this->headerWrapper = new HeaderWrapper();
}

Sender::~Sender() {

}

void Sender::handle() {
    //TODO handling queuing messages to send
    void* buffer = (char *) "elo320fsdsdfds";
    MessageDTO *messageDTO = headerWrapper->createMessage();
    write(this->socketDescriptor, buffer, strlen((const char *) buffer));
}









