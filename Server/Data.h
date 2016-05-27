//
// Created by tomasz on 06.05.16.
//

#ifndef SERVER_MESSAGEDTO_H
#define SERVER_MESSAGEDTO_H


#include "Header.h"
#include "DataType.h"

class Data {
public:

    Data(DataType type, unsigned char *content);

    ~Data();

    DataType getDataType() const { return type; }

    unsigned char *getContent() const { return content; }

private:

    unsigned char *content;

    DataType type;
};


#endif //SERVER_MESSAGEDTO_H
