//
// Created by tomasz on 06.05.16.
//

#ifndef SERVER_MESSAGEDTO_H
#define SERVER_MESSAGEDTO_H


#include "Header.h"

class MessageDTO {
public:
    MessageDTO(Header *header, char *data);
    ~MessageDTO();
private:
    Header *header;
    char *data;

};


#endif //SERVER_MESSAGEDTO_H
