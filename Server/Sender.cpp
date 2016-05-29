//
// Created by tomasz on 05.05.16.
//


#include <cstring>
#include <iostream>
#include "Sender.h"

std::string Sender::MODULE_NAME = "Sender";

Sender::Sender(int socketDescriptor) {
    this->atomicQueue = new AtomicQueue<Data*>(MODULE_NAME + std::to_string(socketDescriptor));
    this->tcpSender = new TCPSender(socketDescriptor);
    this->socketDescriptor = socketDescriptor;
    this->running = false;
}

Sender::~Sender() {
    delete atomicQueue;
    delete tcpSender;
}

void Sender::handle() {
    Data *dataFromQueue;
    this->running = true;
    while(isRunning()) {
        dataFromQueue = atomicQueue->pop();
        sendData(dataFromQueue);
    }
}

void Sender::sendData(Data *data) {
    if(data == nullptr) {
        return;
    }
    switch(data->getType()) {
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

void Sender::sendConnection(Data *data) const {
    log("Sending data type CONNECTION");
    tcpSender->sendConnectionInfo(data->getContent(), data->getSize());
}

void Sender::sendVotes(Data *data) const {
    log("Sending data type VOTES");
    tcpSender->sendVotes(data->getContent(), data->getSize());
}

void Sender::sendStream(Data *data) const {
    log("Sending data type STREAM");
    tcpSender->sendMusic(data->getContent(), data->getSize());
}

void Sender::addMessage(Data *message) {
    this->atomicQueue->push(message);
}

void Sender::wrongDataType() {
    log("Unknown operation type");
}

void Sender::log(std::string message) const {
    std::cout << MODULE_NAME << this->socketDescriptor << ": " <<  message << std::endl << std::flush;
}