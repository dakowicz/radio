//
// Created by tomasz on 05.05.16.
//

#include "Sender.h"

std::string Sender::MODULE_NAME = "Sender";

void Sender::handle() {
    std::shared_ptr<Data> dataFromQueue;
    while(!isConnectionClosed()) {
        dataFromQueue = atomicQueue.pop();
        sendData(dataFromQueue);
    }
}

void Sender::sendData(std::shared_ptr<Data> data) {
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

void Sender::sendConnection(std::shared_ptr<Data> data) {
    logger.log("Sending data type CONNECTION");
    tcpSender.sendConnectionInfo(data->getContent(), data->getSize());
}

void Sender::sendVotes(std::shared_ptr<Data> data) {
    logger.log("Sending data type VOTES");
    tcpSender.sendVotes(data->getContent(), data->getSize());
}

void Sender::sendStream(std::shared_ptr<Data> data) {
    logger.log("Sending data type STREAM");
    tcpSender.sendMusic(data->getContent(), data->getSize());
}

void Sender::addMessage(std::shared_ptr<Data> message) {
    this->atomicQueue.push(message);
}

void Sender::wrongDataType() {
    logger.log("Unknown operation type");
}

bool Sender::isConnectionClosed() {
    return tcpSender.isConnectionClosed();
}

void Sender::setConnectionClosed() {
    tcpSender.setConnectionClosed();
}