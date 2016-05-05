//
// Created by tomasz on 06.05.16.
//

#include "MessageDTO.h"

MessageDTO::MessageDTO(Header *header, char *data) {
    this->header = header;
    this->data = data;
}

MessageDTO::~MessageDTO() {

}



