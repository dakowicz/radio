//
// Created by tomasz on 24.05.16.
//

#include <cstdint>
#include <unistd.h>
#include <cstring>
#include "TCPSender.h"
#include "Header.h"

TCPSender::TCPSender(int socketDescriptor) {
    this->socketDescriptor = socketDescriptor;
}

TCPSender::~TCPSender() {

}

void TCPSender::sendMusic(uint8_t* message) {
    unsigned char* header = Header::createHeaderStream();
    send(header, message);
}

void TCPSender::sendVotes(uint8_t* message) {
    unsigned char* header = Header::createHeaderVote();
    send(header, message);
}

void TCPSender::sendConnectionInfo(uint8_t *message) {
    unsigned char* header = Header::createHeaderConnect();
    send(header, message);
}

void TCPSender::send(uint8_t *header, uint8_t *message) {
    uint8_t* dataToSend = new unsigned char(sizeof(header) + sizeof(message));
    memcpy(dataToSend, header, sizeof(header));
    memcpy(dataToSend + sizeof(dataToSend), message, sizeof(message));
    write(socketDescriptor, dataToSend, sizeof(dataToSend));
}