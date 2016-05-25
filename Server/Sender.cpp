//
// Created by tomasz on 05.05.16.
//


#include <cstring>
#include <iostream>
#include "Sender.h"


Sender::Sender(int socketDescriptor) {
    this->messageQueue = new BlockingQueue<Data*>;
    this->tcpSender = new TCPSender(socketDescriptor);
}

Sender::~Sender() {

}

void Sender::handle() {
    Data* dataFromQueue;
    this->running = true;

    while(running) {
        dataFromQueue = messageQueue->pop();
        sendData(dataFromQueue);
    }
}

void Sender::sendData(Data *data) {

    switch(data->getDataType()){
        case DataType::STREAM:
            tcpSender->sendMusic(data->getContent());
            break;
        case DataType::VOTE:
            tcpSender->sendVotes(data->getContent());
            break;
        case DataType::CONNECTION:
            tcpSender->sendConnectionInfo(data->getContent());
            break;
        case DataType::MUSIC_FILE:
            log("Unknown operation type");
            break;
    }
}

void Sender::addMessage(Data *message) {
    this->messageQueue->push(message);
}

void Sender::log(const char *message) {
    std::cout << message << std::endl;
}