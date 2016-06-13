//
// Created by tomasz on 05.05.16.
//

#ifndef SERVER_SENDER_H
#define SERVER_SENDER_H


#include <unistd.h>
#include <atomic>
#include "TCPSender.h"
#include "Data.h"
#include "AtomicQueue.h"

class Sender {
public:

    Sender(int newSocketDescriptor) :
            atomicQueue(MODULE_NAME + std::to_string(newSocketDescriptor)), tcpSender(newSocketDescriptor), socketDescriptor(newSocketDescriptor), logger(MODULE_NAME, socketDescriptor) {};

    void handle();

    void addMessage(std::shared_ptr<Data> message);

    void setConnectionClosed();

private:

    void wrongDataType();

    AtomicQueue<std::shared_ptr<Data>> atomicQueue;

    TCPSender tcpSender;

    Logger logger;

    int socketDescriptor;

    std::atomic<bool> running;

    static std::string MODULE_NAME;

    void sendConnection(std::shared_ptr<Data> data);

    void sendVotes(std::shared_ptr<Data> data);

    void sendData(std::shared_ptr<Data> data);

    void sendStream(std::shared_ptr<Data> data);

    bool isConnectionClosed();
};


#endif //SERVER_SENDER_H
