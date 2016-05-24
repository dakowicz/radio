//
// Created by tomasz on 05.05.16.
//


#include <iostream>
#include "Dispatcher.h"


Dispatcher::Dispatcher() {
    blockingQueue = new BlockingQueue<Data*>();
}

Dispatcher::~Dispatcher() {
    delete blockingQueue;
}

void Dispatcher::addMessage(Data *newMessage) {
    blockingQueue->push(newMessage);
}

void Dispatcher::start() {
    //todo add strategy of processing messages
    Data *newMessage;
    while(running) {
        newMessage = blockingQueue->pop();
        processMessage(newMessage);
    }
}

void Dispatcher::processMessage(Data *data) {

}












