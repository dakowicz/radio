//
// Created by tomasz on 05.05.16.
//


#include "SocketListener.h"

std::string SocketListener::MODULE_NAME = "SocketListener";

SocketListener::SocketListener(const std::shared_ptr<Dispatcher> &dispatcher, int newSocketDescriptor) {
    this->tcpListener = new TCPListener(newSocketDescriptor);
    this->dispatcher = dispatcher;
    this->socketDescriptor = newSocketDescriptor;
}


SocketListener::~SocketListener() {
    delete tcpListener;
}

void SocketListener::handle() {
    this->running = true;
    while(isRunning()) {
        waitForRequest();
        Data *newMessage = readMessage();
        if(newMessage != nullptr) {
            dispatcher->addMessage(newMessage);
        }
    }
}

Data *SocketListener::readMessage() const {
    Data *newMessage = tcpListener->readMessage();
    return newMessage;
}

void SocketListener::log(std::string message) {
    std::cout << MODULE_NAME << this->socketDescriptor << ": " <<  message << std::endl << std::flush;
}

void SocketListener::waitForRequest() {
    std::unique_lock<std::mutex> lock(mutex);
    while(readRequestsCounter == 0) {
        cond.wait(lock);
    }
    readRequestsCounter--;
}

void SocketListener::addReadRequest() {
    std::unique_lock<std::mutex> lock(mutex);
    readRequestsCounter++;
    lock.unlock();
    cond.notify_one();
}







