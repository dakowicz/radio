//
// Created by tomasz on 06.05.16.
//

#include "Data.h"

char Data::DEFAULT_PARAMETER(4);

Data::~Data() {
    delete[] this->content;
}

bool Data::getBool() {
    return parameters;
}

















