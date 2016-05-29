//
// Created by tomasz on 06.05.16.
//

#include "Data.h"

Data::Data(DataType type, unsigned char *content, int size) {
    this->content = content;
    this->type = type;
    this->size = size;
}

Data::~Data() {
    delete[] this->content;
}










