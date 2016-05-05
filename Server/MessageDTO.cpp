//
// Created by tomasz on 06.05.16.
//

#include "MessageDTO.h"

MessageDTO::MessageDTO(Header *header, char *data) {
    this->header = header;
    this->data = data;

    this->wholeMessage = getMergedMessage();
}

MessageDTO::~MessageDTO() {

}

const void * MessageDTO::getWholeMessage()const {

    return ;
}

void *MessageDTO::getMergedMessage() {
    memcpy(wholeMessage, );
}







