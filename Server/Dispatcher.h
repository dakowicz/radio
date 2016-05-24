//
// Created by tomasz on 05.05.16.
//

#ifndef SERVER_DISPATCHER_H
#define SERVER_DISPATCHER_H


#include "Data.h"
#include "BlockingQueue.h"
#include "BlockingQueue.cpp"

#include <thread>

class Dispatcher {

public:
    Dispatcher();
    ~Dispatcher();

    void start();

    void addMessage(Data* newMessage);

private:
    BlockingQueue<Data*> *blockingQueue;

    bool running;

    void processMessage(Data* data);

};


#endif //SERVER_DISPATCHER_H
