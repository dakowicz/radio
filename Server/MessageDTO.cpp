//
// Created by tomasz on 06.05.16.
//

#include <cstring>
#include "MessageDTO.h"

MessageDTO::MessageDTO(uint8_t *headerData, uint8_t *data) {
    this->headerData = headerData;
    this->data = data;

    this->wholeMessage = getMergedMessage();

}

MessageDTO::~MessageDTO() {

}

const uint8_t *MessageDTO::getWholeMessage()const {

    return this->wholeMessage;
}

uint8_t *MessageDTO::getMergedMessage() {
    //TODO return whole message (not only header)
    this->wholeMessage = new uint8_t[7];
    memcpy(this->wholeMessage, this->headerData, 7 );
}







