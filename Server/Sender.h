//
// Created by tomasz on 05.05.16.
//

#ifndef SERVER_SENDER_H
#define SERVER_SENDER_H


#include "SocketListener.h"
#include "TCPSender.h"
#include <unistd.h>

class Sender
{

public:
    Sender(int socketDescriptor);
    ~Sender();

    void handle();
    void addMessage(Data* message);

    bool isRunning() const { return running; }
    void setRunning(bool val) { this-> running = val;}

private:

    void sendData(Data *data);

    void log(const char *string);

    BlockingQueue<Data*> *messageQueue;
    bool running;
    TCPSender *tcpSender;
};


#endif //SERVER_SENDER_H
