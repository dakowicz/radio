//
// Created by tomasz on 24.05.16.
//

#include <cstdint>
#include <unistd.h>
#include <cstring>
#include "TCPSender.h"
#include "Header.h"

std::string TCPSender::MODULE_NAME = "TCPSender";

TCPSender::TCPSender(int socketDescriptor) {
    this->socketDescriptor = socketDescriptor;
}

TCPSender::~TCPSender() {
}

void TCPSender::sendMusic(unsigned  char *message) {
    unsigned char *header = Header::createHeaderStream();
    send(header, message);
}

void TCPSender::sendVotes(unsigned  char *message) {
    unsigned char *header = Header::createHeaderVote();
    send(header, message);
}

void TCPSender::sendConnectionInfo(unsigned char *message) {
    unsigned char *header = Header::createHeaderConnect();
    send(header, message);
}

void TCPSender::send(unsigned char *header, unsigned char *message) {
    unsigned char *dataToSend = new unsigned char [sizeof(header) + sizeof(message)];
    addHeader(header, dataToSend);
    addMessage(message, dataToSend);
    write(socketDescriptor, dataToSend, sizeof(dataToSend));
}

void TCPSender::addMessage(unsigned char *message, unsigned char *dataToSend) const {
    if(message != nullptr) {
        memcpy(dataToSend + sizeof(dataToSend), message, sizeof(message));
    }
}

void TCPSender::addHeader(unsigned char *header, unsigned char *dataToSend) const {
    if(header != nullptr) {
        memcpy(dataToSend, header, sizeof(header));
    }
}