//
// Created by tomasz on 25.05.16.
//


#include "TCPListener.h"

TCPListener::TCPListener(int socketDescriptor) {
    this->socketDescriptor = socketDescriptor;
    readyToRead = false;
}

TCPListener::~TCPListener() {

}

Data *TCPListener::readMessage() {
    if(!headerReady) {
        readHeader();
    }
    else{
        if(messageBuffer == nullptr) {
            messageBuffer = new unsigned char(header->getLength());
        }

        unsigned char *data = nullptr;
        data = readN(header->getLength());
        if(data != nullptr){
            return new Data( (DataType)header->getType(), data);
        }
    }
    return nullptr;
}

void TCPListener::readHeader() {
    if(messageBuffer == nullptr) {
        messageBuffer = new unsigned char(Header::HEADER_LENGTH);
    }

    unsigned char *head = nullptr;
    head = readN(Header::HEADER_LENGTH);
    if(head != nullptr){
            headerReady = true;
            header = Header::createHeader(messageBuffer);
            delete[] messageBuffer;
            messageBuffer = nullptr;
        }
}

unsigned char *TCPListener::readN(int totalBytesNumber) {
    if(readyToRead) {
        int bytesToRead = totalBytesNumber - this->collectedBytes;
        unsigned char messagePortion[bytesToRead];

        int n = read(this->socketDescriptor, messagePortion, bytesToRead);
        if (n < 0) {
            perror("ERROR reading from socket\n");
        }
        else {
            readyToRead = false;
            memcpy(messageBuffer + sizeof(messageBuffer), messagePortion, n);
            collectedBytes += n;

            if (totalBytesNumber == this->collectedBytes) {
                collectedBytes = 0;
                return this->messageBuffer;
            }
        }

        return nullptr;
    }
}

void TCPListener::SetReady() {
    readyToRead = true;
}







