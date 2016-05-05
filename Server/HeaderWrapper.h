//
// Created by tomasz on 05.05.16.
//

#ifndef SERVER_HEADERWRAPPER_H
#define SERVER_HEADERWRAPPER_H


#include "MessageDTO.h"

class HeaderWrapper {

public:
    HeaderWrapper();
    ~HeaderWrapper();

    MessageDTO *createMessage(char *data);
};


#endif //SERVER_HEADERWRAPPER_H
