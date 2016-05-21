//
// Created by tomasz on 05.05.16.
//

#ifndef SERVER_SENDER_H
#define SERVER_SENDER_H


#include "HeaderWrapper.h"
#include "SocketListener.h"
#include <unistd.h>

class Sender
{

public:
    Sender(int socketDescriptor);
    ~Sender();

    void handle();

private:
    int socketDescriptor;
    HeaderWrapper* headerWrapper;

    void sendMessage(const char *buffer) const;

    void sendMessage(const MessageDTO *messageDTO) const;
};


#endif //SERVER_SENDER_H
