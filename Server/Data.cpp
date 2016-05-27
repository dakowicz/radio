//
// Created by tomasz on 06.05.16.
//

#include "Data.h"

Data::Data(DataType type, unsigned char *content) {
    this->content = content;
    this->type = type;
}

Data::~Data() {
    delete[] this->content;
}










