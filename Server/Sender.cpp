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
    char* buffer = (char *) "elo320fsdsdfds";
    MessageDTO *messageDTO = headerWrapper->createMessage(buffer);
    sendMessage(buffer);
}

void Sender::sendMessage(const MessageDTO *messageDTO)  const {
    const void *buffer = messageDTO->getWholeMessage();
    write(this->socketDescriptor, buffer, strlen((const char *) buffer));
}









