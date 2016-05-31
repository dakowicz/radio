//
// Created by tomasz on 25.05.16.
//


#include "TCPListener.h"

std::string TCPListener::MODULE_NAME = "TCPListener";

Data * TCPListener::readMessage() {
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
    if(contentBuffer == nullptr) {
        contentBuffer = new char[header->getLength()];
        bytesToRead = header->getLength();
        bytesAlreadyRead = 0;
    }
    readBytes(contentBuffer);
    checkIfMessageComplete();
}

void TCPListener::readHeader() {
    if(headerBuffer == nullptr) {
        resetHeader();
        contentBuffer = nullptr;
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
    logger.log("Loaded " + std::to_string(payload));
    if(isReadSuccessful(payload)) {
        updatePayload(payload);
    }else if(connectionHasBeenClosed(payload)) {
        //closeConnection();
    } else {
        checkErrorCode(payload);
    }
}

bool TCPListener::connectionHasBeenClosed(int payload) const { return payload == 0; }

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
//    logger->log(std::to_string(payload));
}