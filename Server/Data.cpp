//
// Created by tomasz on 06.05.16.
//

#include <cstring>
#include "Data.h"

Data::Data(DataType type, uint8_t *content) {
    this->content = content;
    this->type = type;
}

Data::~Data() {
    delete[] this->content;
}










