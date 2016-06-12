//
// Created by tomasz on 06.05.16.
//

#include "Data.h"

Data::Data(DataType type, char *content, int size) {
    this->content = content;
    this->type = type;
    this->size = size;
}

Data::~Data() {
    delete[] this->content;
}

Data::Data(DataType type, char *content, int size, bool flag) {
    this->content = content;
    this->type = type;
    this->size = size;
    this->flag = flag;
}

bool Data::getBool() {
    return flag;
}














