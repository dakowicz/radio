//
// Created by tomasz on 05.05.16.
//


#include <cstring>
#include "Sender.h"
#include "Header.h"
#include "TCPSender.h"
#include "Data.h"


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
        case DataType::MUSIC:
            tcpSender->sendMusic(data->getContent());
            break;
        case DataType::VOTES:
            tcpSender->sendVotes(data->getContent());
            break;
    }
}













