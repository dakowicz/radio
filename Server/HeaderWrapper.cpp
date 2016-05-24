//
// Created by tomasz on 05.05.16.
//

#include <stddef.h>
#include "HeaderWrapper.h"

HeaderWrapper::HeaderWrapper() {

}

HeaderWrapper::~HeaderWrapper() {

}

Data *HeaderWrapper::createMessage(void *data) {

    //uint8_t headerData[7] = {2, 0, 1, 0, 0, 0, 0 };
    Header *header = new Header();
    header->createHeaderConnect(true, false, 0);

    //TODO
    return nullptr;
}





