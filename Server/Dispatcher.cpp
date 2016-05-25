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

void Dispatcher::start() {
    Data *newMessage;
    this->running = true;

    while(running) {
        newMessage = blockingQueue->pop();
        processMessage(newMessage);
    }
}

void Dispatcher::addMessage(Data *newMessage) {
    if(newMessage == nullptr){
        return;
    }

    this->blockingQueue->push(newMessage);
    log("Pushed messege to the queue");
}

void Dispatcher::processMessage(Data *data) {
    if(data == nullptr){
        return;
    }

    switch(data->getDataType()) {
        case DataType::VOTE:
            processVote(data);
            break;
        case DataType::MUSIC_FILE:
            processMusicFile(data);
            break;
        case DataType::CONNECTION:
            processConnectionMessage(data);
            break;
        case DataType::STREAM:
            wrongDataType();
    }
}

void Dispatcher::log(const char *message) const { std::cout << "Dispatcher: " << message << std::endl; }

void Dispatcher::processVote(Data *data) {
    log("Processing VOTE");
}

void Dispatcher::processMusicFile(Data *data) {
    log("Processing MUSIC_FILE");
}

void Dispatcher::processConnectionMessage(Data *data) {
    log("Processing CONNECTION");
}

void Dispatcher::wrongDataType() {
    log("Wrong data type");
}






















