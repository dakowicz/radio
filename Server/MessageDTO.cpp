//
// Created by tomasz on 06.05.16.
//

#include <cstring>
#include "MessageDTO.h"

MessageDTO::MessageDTO(Header *header, uint8_t *data) {
    this->header = header;
    this->data = data;

    this->getMergedMessage();

}

MessageDTO::~MessageDTO() {
    delete this->header;
    delete[] this->data;
    delete[] this->wholeMessage;

}

const uint8_t *MessageDTO::getWholeMessage()const {

    return this->wholeMessage;
}

uint8_t *MessageDTO::getMergedMessage() {
    //TODO return whole message (not only header)
    this->wholeMessage = this->header->createBuffer();
    //memcpy(this->wholeMessage, this->header->createBuffer(), 7 );
}







