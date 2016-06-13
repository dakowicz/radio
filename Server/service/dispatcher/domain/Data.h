//
// Created by tomasz on 06.05.16.
//

#ifndef SERVER_MESSAGEDTO_H
#define SERVER_MESSAGEDTO_H


#include "../../../tcp/domain/Header.h"
#include "DataType.h"

class Data {
public:

    Data(DataType type, const char *content, int size, char parameters = DEFAULT_PARAMETER) :
            type(type), content(content), parameters(parameters), size(size) {}

    ~Data();

    const char * getContent() const { return content; }

    DataType getType() const { return type; }

    int getSize() const { return size; }

    char getParameters() const { return parameters; }

    bool getBool();

private:

    const char *content;

    DataType type;

    int size;

    char parameters;

    static char DEFAULT_PARAMETER;
};


#endif //SERVER_MESSAGEDTO_H
