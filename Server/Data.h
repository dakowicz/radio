//
// Created by tomasz on 06.05.16.
//

#ifndef SERVER_MESSAGEDTO_H
#define SERVER_MESSAGEDTO_H


#include "Header.h"
#include "DataType.h"

class Data {
public:

    Data(DataType type, unsigned char *content, int size);

    ~Data();

    unsigned char *getContent() const { return content; }

    DataType getType() const { return type; }

    int getSize() const { return size; }

private:

    unsigned char *content;

    DataType type;

    int size;
};


#endif //SERVER_MESSAGEDTO_H
