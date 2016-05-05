//
// Created by tomasz on 05.05.16.
//

#include "HeaderWrapper.h"

HeaderWrapper::HeaderWrapper() {

}

HeaderWrapper::~HeaderWrapper() {

}

MessageDTO *HeaderWrapper::createMessage(char *data) {

    uint8_t headerData[7] = {2, 0, 1, 0, 0, 0, 0 };
    Header *header = new Header(headerData);

    return 0;
}





