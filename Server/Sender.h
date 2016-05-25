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

    void log(const char *string)const;

    BlockingQueue<Data*> *blockingQueue;
    bool running;
    TCPSender *tcpSender;
    int socketDescriptor;

    void sendStream(const Data *data) const;

    void sendVotes(const Data *data) const;

    void sendConnection(const Data *data) const;

    void wrongDataType();
};


#endif //SERVER_SENDER_H
