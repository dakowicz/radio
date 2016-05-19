//
// Created by tomasz on 05.05.16.
//


#include <iostream>
#include "Dispatcher.h"


Dispatcher::Dispatcher() {
    blockingQueue = new BlockingQueue<MessageDTO*>();
}

Dispatcher::~Dispatcher() {
    delete blockingQueue;
}

void Dispatcher::addMessage(MessageDTO *newMessage) {
    blockingQueue->push(newMessage);

}

void Dispatcher::handleMessages(BlockingQueue<MessageDTO*> *blockingQueue) {
    //todo add strategy of messages, something like headerfactory
    while(1) {
        MessageDTO *newMessage;
        blockingQueue->pop(newMessage);

        //print data
        if(newMessage!= nullptr) {
            std::cout << "header: ";
            const uint8_t *wholeMessage = newMessage->getWholeMessage();
            for (int i = 0; i < 7; i++) {
                std::cout << (int) wholeMessage[i] << ", ";
            }

            uint8_t *data = newMessage->getData();
            std::cout << " message data: " << std::endl;
            for (int i = 0; i < newMessage->getHeader()->getLength(); i++) {
                std::cout << (int) data[i] << ", ";
            }
            std::cout << std::endl;
        }

        if(newMessage != nullptr){
            delete newMessage;
            newMessage = nullptr;
        }

        //new Strategy(newMessage)
    }
}

void Dispatcher::startHandling() {
    std::thread *dispatcherThread = new std::thread(handleMessages, this->blockingQueue);
}










