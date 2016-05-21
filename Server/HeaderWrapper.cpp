//
// Created by tomasz on 05.05.16.
//

#include "HeaderWrapper.h"

HeaderWrapper::HeaderWrapper() {

}

HeaderWrapper::~HeaderWrapper() {

}

MessageDTO *HeaderWrapper::createMessage(void *data) {

    //uint8_t headerData[7] = {2, 0, 1, 0, 0, 0, 0 };
    Header *header = new Header();
    header->createHeaderConnect(true, false, 0);

    return new MessageDTO(header, (uint8_t*)data);
}





