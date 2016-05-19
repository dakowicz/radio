//
// Created by tomasz on 05.05.16.
//

#ifndef SERVER_DISPATCHER_H
#define SERVER_DISPATCHER_H


#include "MessageDTO.h"
#include "BlockingQueue.h"
#include "BlockingQueue.cpp"

#include <thread>

class Dispatcher {

public:
    Dispatcher();
    ~Dispatcher();

    void addMessage(MessageDTO *newMessage);


    void startHandling();

private:
    BlockingQueue<MessageDTO *> *blockingQueue;

    void static handleMessages(BlockingQueue<MessageDTO*> *blockingQueue);
};


#endif //SERVER_DISPATCHER_H
