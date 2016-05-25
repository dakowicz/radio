//
// Created by tomasz on 06.05.16.
//

<<<<<<< Updated upstream
#include <cstring>
#include "Data.h"

Data::Data(DataType type, uint8_t *content) {
=======
#include "Data.h"

Data::Data(DataType type, unsigned char* content) {
>>>>>>> Stashed changes
    this->content = content;
    this->type = type;
}

Data::~Data() {
    delete[] this->content;
}










