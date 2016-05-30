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
//    std::string fileName = std::string("/home/tomasz/prog/radio/Server/") + std::string("newfile") + std::to_string(socketDescriptor);
//    this->file = new std::ofstream(fileName);
}

TCPSender::~TCPSender() {
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
    int dataToSendSize = Header::SIZE + messageSize;
    char *dataToSend = new char [dataToSendSize];
    addHeader(header, dataToSend);
    addMessage(message, dataToSend, messageSize);
    writeData(dataToSend, dataToSendSize);
    log(std::to_string(dataToSendSize));
//    if(dataToSendSize < 200000)
//        file->close();
}

void TCPSender::writeData(char *dataToSend, int dataToSendSize) const {
//    file->write(dataToSend, dataToSendSize);
    write(socketDescriptor, dataToSend, dataToSendSize);
}

void TCPSender::addHeader(char *header, char *dataToSend) const {
    if(header != nullptr) {
        memcpy(dataToSend, header, getHeaderSize());
    }
}

int TCPSender::getHeaderSize() const { return Header::SIZE; }

void TCPSender::addMessage(char *message, char *dataToSend, size_t messageSize) const {
    if(message != nullptr) {
        memcpy(dataToSend + getHeaderSize(), message, messageSize);
    }
}

void TCPSender::log(std::string message) {
    std::cout << MODULE_NAME << this->socketDescriptor << ": " << message << std::endl << std::flush;
}

