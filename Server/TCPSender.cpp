//
// Created by tomasz on 24.05.16.
//

#include <sys/socket.h>
#include "TCPSender.h"
#include "Header.h"


std::string TCPSender::MODULE_NAME = "TCPSender";

void TCPSender::sendMusic(char *message, int messageSize) {
    char *header = Header::createHeaderStream();
    sendMessage(header, message, messageSize);
}

void TCPSender::sendVotes(char *message, int messageSize) {
    char *header = Header::createHeaderVote();
    sendMessage(header, message, messageSize);
}

void TCPSender::sendConnectionInfo(char *message, int messageSize) {
    char *header = Header::createHeaderConnect();
    sendMessage(header, message, messageSize);
}

void TCPSender::sendMessage(char *header, char *message, int messageSize) {
    writeData(header, Header::SIZE);
    writeData(message, messageSize);
//    if(messageSize < 80000)
//        file->close();
}

void TCPSender::writeData(char *dataToSend, int dataToSendSize) {
    if(dataToSend != nullptr) {
//        file->write(dataToSend, dataToSendSize);
        int bytesSent = (int) send(socketDescriptor, dataToSend, dataToSendSize, MSG_NOSIGNAL);
        if ( bytesSent < 0 && errno == EPIPE) {
            logger.log("EPIPE error");
            setConnectionClosed();
        } else {
            logger.log(std::to_string(bytesSent));
        }
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

void TCPSender::setConnectionClosed() {
    connectionClosed = true;
}

bool TCPSender::isConnectionClosed() {
    return connectionClosed.load();
}






