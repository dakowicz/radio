//
// Created by tomasz on 05.05.16.
//

#ifndef SERVER_DISPATCHER_H
#define SERVER_DISPATCHER_H


#include "Data.h"
#include "BlockingQueue.h"
#include <thread>

class Dispatcher {

public:

    Dispatcher();

    ~Dispatcher();

    void start();

    void addMessage(Data* newMessage);

private:

    void processMessage(Data* data);

    void processVote(Data *data);

    void wrongDataType();

    void processMusicFile(Data *data);

    void processConnectionMessage(Data *data);

    bool running;

    BlockingQueue<Data*> *blockingQueue;

    static std::string MODULE_NAME;

    void log(std::string message) const;

    bool isMessageEmpty(const Data *newMessage) const;
};


#endif //SERVER_DISPATCHER_H
