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
<<<<<<< Updated upstream
=======
    void addMessage(Data* message);

>>>>>>> Stashed changes
    bool isRunning() const { return running; }
    void setRunning(bool val) { this-> running = val;}

private:

<<<<<<< Updated upstream
    int socketDescriptor;
    BlockingQueue<Data*> *messageQueue;
    bool running;
    TCPSender *tcpSender;

    void sendData(Data *data);
=======
    void sendData(Data *data);

    void log(const char *string);

    BlockingQueue<Data*> *messageQueue;
    bool running;
    TCPSender *tcpSender;
>>>>>>> Stashed changes
};


#endif //SERVER_SENDER_H
