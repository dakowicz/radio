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
    uint8_t *dataBuffer;//data to send should be in buffer
    MessageDTO *messageDTO = headerWrapper->createMessage(dataBuffer);
    sendMessage(messageDTO);
}

void Sender::sendMessage(const MessageDTO *messageDTO)  const {
    const uint8_t *buffer = messageDTO->getWholeMessage();

    write(this->socketDescriptor, buffer, 7);//strlen((const char *) buffer)
}









