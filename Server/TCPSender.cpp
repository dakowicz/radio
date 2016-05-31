//
// Created by tomasz on 24.05.16.
//

#include <cstdint>
#include <unistd.h>
#include <fstream>
#include <cstring>
#include <iostream>
#include "TCPSender.h"
#include "Header.h"

std::string TCPSender::MODULE_NAME = "TCPSender";

TCPSender::TCPSender(int socketDescriptor) {
    this->socketDescriptor = socketDescriptor;
    this->logger = new Logger(MODULE_NAME, socketDescriptor);
//    std::string fileName = std::string("/home/tomasz/prog/radio/Server/") + std::string("newfile") + std::to_string(socketDescriptor);
//    this->file = new std::ofstream(fileName);
}

TCPSender::~TCPSender() {
    delete logger;
}

void TCPSender::sendMusic(char *message, int messageSize) {
    char *header = Header::createHeaderStream();
    send(header, message, messageSize);
}

void TCPSender::sendVotes(char *message, int messageSize) {
    char *header = Header::createHeaderVote();
    send(header, message, messageSize);
}

void TCPSender::sendConnectionInfo(char *message, int messageSize) {
    char *header = Header::createHeaderConnect();
    send(header, message, messageSize);
}

void TCPSender::send(char *header, char *message, int messageSize) {
    writeData(header, Header::SIZE);
    writeData(message, messageSize);
//    if(messageSize < 80000)
//        file->close();
}

void TCPSender::writeData(char *dataToSend, int dataToSendSize) const {
    if(dataToSend != nullptr) {
//        file->write(dataToSend, dataToSendSize);
        int n = (int) write(socketDescriptor, dataToSend, dataToSendSize);
        logger->log(std::to_string(dataToSendSize));
    }
}

void TCPSender::addHeader(char *header, char *dataToSend) {
    if(header != nullptr) {
        memcpy(dataToSend, header, Header::SIZE);
        pointerPosition += Header::SIZE;
    }
}

void TCPSender::addMessage(char *message, char *dataToSend, int messageSize) const {
    if (message != nullptr) {
        memcpy(dataToSend + pointerPosition, message, messageSize);
    }
}


