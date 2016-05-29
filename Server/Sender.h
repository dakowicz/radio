//
// Created by tomasz on 05.05.16.
//

#ifndef SERVER_SENDER_H
#define SERVER_SENDER_H


#include "SocketListener.h"
#include "TCPSender.h"
#include <unistd.h>
#include <atomic>

class Sender {
public:

    Sender(int socketDescriptor);

    ~Sender();

    void handle();

    const bool isRunning() const { return running.load(); }

    void setRunning(bool val) { this->running = val; }

    void addMessage(Data *message);

private:

    void wrongDataType();

    std::shared_ptr<AtomicQueue<Data *>> atomicQueue;

    std::atomic<bool> running;

    std::shared_ptr<TCPSender> tcpSender;

    int socketDescriptor;

    static std::string MODULE_NAME;

    void log(std::string message) const;

    void sendConnection(Data *data) const;

    void sendVotes(Data *data) const;

    void sendData(Data *data);

    void sendStream(Data *data) const;

};


#endif //SERVER_SENDER_H
