//
// Created by tomasz on 05.05.16.
//

#ifndef SERVER_HEADERWRAPPER_H
#define SERVER_HEADERWRAPPER_H


#include "Data.h"

class HeaderWrapper {

public:
    HeaderWrapper();
    ~HeaderWrapper();

    Data *createMessage(void *data);
};


#endif //SERVER_HEADERWRAPPER_H
