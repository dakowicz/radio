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
    this->logger = new Logger(MODULE_NAME, socketDescriptor);
    this->running = false;
}

Sender::~Sender() {
    delete atomicQueue;
    delete tcpSender;
    delete logger;
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
    logger->log("Sending data type CONNECTION");
    tcpSender->sendConnectionInfo(data->getContent(), data->getSize());
}

void Sender::sendVotes(Data *data) const {
    logger->log("Sending data type VOTES");
    tcpSender->sendVotes(data->getContent(), data->getSize());
}

void Sender::sendStream(Data *data) const {
    logger->log("Sending data type STREAM");
    tcpSender->sendMusic(data->getContent(), data->getSize());
}

void Sender::addMessage(Data *message) {
    this->atomicQueue->push(message);
}

void Sender::wrongDataType() {
    logger->log("Unknown operation type");
}