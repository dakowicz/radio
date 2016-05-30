//
// Created by tomasz on 25.05.16.
//

#include <iostream>
#include <memory>
#include "TCPListener.h"
#include "ConnectionType.h"

std::string TCPListener::MODULE_NAME = "TCPListener";

TCPListener::TCPListener(int socketDescriptor) {
    this->socketDescriptor = socketDescriptor;
    isHeaderComplete = false;
    isMessageComplete = false;
    bytesAlreadyRead = 0;
    bytesToRead = 0;
    this->header = nullptr;
    this->contentBuffer = nullptr;
    this->headerBuffer = nullptr;
}

TCPListener::~TCPListener() {
}

Data *TCPListener::readMessage() {
    if(isHeaderComplete) {
        readMessageContent();
    } else {
        readHeader();
    }
    return getMessage();
}

Data *TCPListener::getMessage() const {
    if(isConnectionClosed){
        return new Data(DataType::CLOSED, nullptr, 0);
    }
    if(isMessageComplete){
        return new Data((DataType) header->getType(), contentBuffer, header->getLength());
    }
    return nullptr;
}

void TCPListener::readMessageContent() {
    if(contentBuffer != nullptr) {
        contentBuffer = new char[header->getLength()];
        bytesToRead = header->getLength();
        bytesAlreadyRead = 0;
    }
    readBytes(contentBuffer);
    checkIfMessageComplete();
}

void TCPListener::readHeader() {
    if(headerBuffer != nullptr) {
        resetHeader();
        headerBuffer = new char[Header::SIZE];
        bytesToRead = Header::SIZE;
        bytesAlreadyRead = 0;
    }
    readBytes(headerBuffer);
    checkIfHeaderComplete();
}

void TCPListener::resetHeader() {
    delete header;
    header = nullptr;
}

void TCPListener::readBytes(char *buffer) {
    int payload = (int) read(socketDescriptor, buffer + bytesAlreadyRead, bytesToRead);
    log("Loaded " + std::to_string(payload));
    if(isReadSuccessful(payload)) {
        updatePayload(payload);
    }else if(hasConnectionBeenClosed(payload)) {
        //closeConnection();
    } else {
        checkErrorCode(payload);
    }
}

bool TCPListener::hasConnectionBeenClosed(int payload) const { return payload == 0; }

bool TCPListener::isReadSuccessful(int payload) const { return payload > 0; }

void TCPListener::updatePayload(int payload) {
    bytesToRead -= payload;
    bytesAlreadyRead += payload;
}

void TCPListener::checkIfHeaderComplete() {
    if(isReadingComplete()) {
        isHeaderComplete = true;
        isMessageComplete = false;
        header = Header::createHeader(headerBuffer);
        resetHeaderBuffer();
    }
}

void TCPListener::resetHeaderBuffer() {
    delete[] headerBuffer;
    headerBuffer = nullptr;
}

void TCPListener::checkIfMessageComplete() {
    if(isReadingComplete()) {
        isMessageComplete = true;
        isHeaderComplete = false;
    }
}

bool TCPListener::isReadingComplete() const { return bytesToRead == 0; }

void TCPListener::closeConnection() {
    isConnectionClosed = true;
}

void TCPListener::checkErrorCode(int payload) {
    //log(std::to_string(payload));
}

void TCPListener::log(std::string message) {
    std::cout << MODULE_NAME << this->socketDescriptor << ": " << message << std::endl << std::flush;
}





















/*

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
            messageBuffer = nullptr;
            headerReady = false;
            return new Data( (DataType)header->getType(), (char*)data, header->getLength());//todo casting is needed?
        }
    }
    return nullptr;
}

void TCPListener::readHeader() {
    if(messageBuffer == nullptr) {
        messageBuffer = new unsigned char(Header::SIZE);
    }

    unsigned char *head = nullptr;
    head = readN(Header::SIZE);
    if(head != nullptr){
        headerReady = true;
        if(header != nullptr){
            delete header;
        }
        header = Header::createHeader(messageBuffer);
        delete[] messageBuffer;
        messageBuffer = nullptr;
    }
}

unsigned char *TCPListener::readN(int totalBytesNumber) {
    int bytesToRead = totalBytesNumber - this->collectedBytes;
    char *messagePortion = new char[bytesToRead];

    int n = read(this->socketDescriptor, messagePortion, bytesToRead);
    int err = errno;
    if (n < 0) {
        checkReadError(err);
    } else {
        copyReadData(messagePortion, n);
        if (isMessageComplete(totalBytesNumber)) {
            collectedBytes = 0;
            return this->messageBuffer;
        }
    }
    return nullptr;
}

bool TCPListener::isMessageComplete(int totalBytesNumber) const { return totalBytesNumber == collectedBytes; }

void TCPListener::copyReadData(char *messagePortion, int n) {
    memcpy(messageBuffer + collectedBytes, messagePortion, n);
    collectedBytes += n;
}

void TCPListener::checkReadError(int err) const {
    if (isUnavailable(err) || wouldBlock(err)) {
            perror("Non-blocking operation returned EAGAIN or EWOULDBLOCK\n");
        } else {
            perror("ERROR reading from socket\n");
        }
}

bool TCPListener::wouldBlock(int err) const { return (err == EWOULDBLOCK); }

bool TCPListener::isUnavailable(int err) const { return (err == EAGAIN); }

*/
