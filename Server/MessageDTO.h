//
// Created by tomasz on 06.05.16.
//

#ifndef SERVER_MESSAGEDTO_H
#define SERVER_MESSAGEDTO_H


#include "Header.h"

class MessageDTO {
public:
    MessageDTO(uint8_t *headerData, uint8_t *data);
    ~MessageDTO();

    const uint8_t *getWholeMessage()const;

private:
    uint8_t *headerData;
    uint8_t *data;
    uint8_t *wholeMessage;

    uint8_t *getMergedMessage();
};


#endif //SERVER_MESSAGEDTO_H
