//
// Created by tomasz on 05.05.16.
//

#ifndef SERVER_DISPATCHER_H
#define SERVER_DISPATCHER_H


#include "Data.h"
#include "SynchronizedStructure.h"
#include "SynchronizedStructure.cpp"

#include <thread>

class Dispatcher {

public:
    Dispatcher();
    ~Dispatcher();

    void start();

    void addMessage(Data* newMessage);

private:
    void processMessage(Data* data);

    bool running;
    SynchronizedStructure<Data*> *blockingQueue;

    void log(const char *message) const;

    void processVote(Data *data);

    void wrongDataType();

    void processMusicFile(Data *data);

    void processConnectionMessage(Data *data);
};


#endif //SERVER_DISPATCHER_H
