//
// Created by tomasz on 05.05.16.
//


#include "SocketListener.h"

std::string SocketListener::MODULE_NAME = "SocketListener";

void SocketListener::handle() {
    this->running = true;
    while(isRunning()) {
        waitForRequest();
        Data *newMessage = readMessage();
        if(newMessage != nullptr) {
            dispatcher.addMessage(newMessage);
        }
    }
}

Data *SocketListener::readMessage() {
    return tcpListener.readMessage();
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
    readRequestsCounter = 1;
    lock.unlock();
    cond.notify_one();
}

void SocketListener::resetReadReaquestCounter() {
    std::unique_lock<std::mutex> lock(mutex);
    readRequestsCounter = 0;
    lock.unlock();
}









