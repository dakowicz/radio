//
// Created by tomasz on 05.05.16.
//

#ifndef SERVER_SENDER_H
#define SERVER_SENDER_H


#include "HeaderWrapper.h"
#include "SocketListener.h"
#include "TCPSender.h"
#include <unistd.h>

class Sender
{

public:
    Sender(int socketDescriptor);
    ~Sender();

    void handle();
    bool isRunning() const { return running; }
    void setRunning(bool val) { this-> running = val;}

private:

    int socketDescriptor;
    BlockingQueue<Data*> *messageQueue;
    bool running;
    TCPSender *tcpSender;

    void sendData(Data *data);
};


#endif //SERVER_SENDER_H
