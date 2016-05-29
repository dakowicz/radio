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
}

TCPSender::~TCPSender() {
}

void TCPSender::sendMusic(unsigned char *message, int messageSize) {
    unsigned char *header = Header::createHeaderStream();
    send(header, message, messageSize);
}

void TCPSender::sendVotes(unsigned char *message, int messageSize) {
    unsigned char *header = Header::createHeaderVote();
    send(header, message, messageSize);
}

void TCPSender::sendConnectionInfo(unsigned char *message, int messageSize) {
    unsigned char *header = Header::createHeaderConnect();
    send(header, message, messageSize);
}

void TCPSender::send(unsigned char *header, unsigned char *message, int messageSize) {
    int dataToSendSize = Header::SIZE + messageSize;
    unsigned char *dataToSend = new unsigned char [dataToSendSize];
    addHeader(header, dataToSend);
    addMessage(message, dataToSend, messageSize);
    writeData(dataToSend, dataToSendSize);
    log(std::to_string(dataToSendSize));
}

void TCPSender::writeData(const unsigned char *dataToSend, int dataToSendSize) const {
    write(socketDescriptor, dataToSend, dataToSendSize);
}

void TCPSender::addHeader(unsigned char *header, unsigned char *dataToSend) const {
    if(header != nullptr) {
        memcpy(dataToSend, header, getHeaderSize());
    }
}

int TCPSender::getHeaderSize() const { return Header::SIZE; }

void TCPSender::addMessage(unsigned char *message, unsigned char *dataToSend, size_t messageSize) const {
    if(message != nullptr) {
        memcpy(dataToSend + getHeaderSize(), message, messageSize);
    }
}

void TCPSender::log(std::string message) {
    std::cout << MODULE_NAME << ": " << message << std::endl << std::flush;
}

