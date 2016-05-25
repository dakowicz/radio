//
// Created by tomasz on 05.05.16.
//


#include <cstring>
#include <iostream>
#include "Sender.h"
#include "BlockingQueue.h"


Sender::Sender(int socketDescriptor) {
    this->messageQueue = new BlockingQueue<Data*>;
    this->socketDescriptor = socketDescriptor;
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
    if(data == nullptr) {
        return;
    }

    switch(data->getDataType()){
        case DataType::STREAM:
            sendStream(data);
            break;
        case DataType::VOTE:
            sendVotes(data);
            break;
        case DataType::CONNECTION:
            sendConnection(data);
            break;
        case DataType::MUSIC_FILE:
            wrongDataType();
            break;
    }
}

void Sender::sendConnection(const Data *data) const {
    log("Sending data type CONNECTION");
    tcpSender->sendConnectionInfo(data->getContent());
}

void Sender::sendVotes(const Data *data) const {
    log("Sending data type VOTES");
    tcpSender->sendVotes(data->getContent());
}

void Sender::sendStream(const Data *data) const {
    log("Sending data type VOTES");
    tcpSender->sendMusic(data->getContent());
}

void Sender::addMessage(Data *message) {
    this->messageQueue->insert(message);
}

void Sender::wrongDataType() { log("Unknown operation type"); }

void Sender::log(const char *message) const {
    std::cout << "Sender " << this->socketDescriptor << ": " <<  message << std::endl << std::flush;
}