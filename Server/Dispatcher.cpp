#include <iostream>
#include "Dispatcher.h"


std::string Dispatcher::MODULE_NAME = "Dispatcher";

Dispatcher::Dispatcher(const std::shared_ptr<FileManager> &fileManager, const std::shared_ptr<PlaylistManager> &playlistManager) {
    this->fileManager = fileManager;
    this->playlistManager = playlistManager;
    this->atomicQueue = new AtomicQueue<Data*>(MODULE_NAME);
    this->logger = new Logger(MODULE_NAME);
}

Dispatcher::~Dispatcher() {
    delete atomicQueue;
    delete logger;
}

void Dispatcher::start() {
    Data *newMessage;
    this->running = true;
    while(isRunning()) {
        newMessage = atomicQueue->pop();
        processMessage(newMessage);
    }
}

void Dispatcher::addMessage(Data *newMessage) {
    if(isMessageEmpty(newMessage)) {
        return;
    }
    this->atomicQueue->push(newMessage);
}

bool Dispatcher::isMessageEmpty(Data *newMessage) const {
    return newMessage == nullptr || newMessage->getContent() == nullptr;
}

void Dispatcher::processMessage(Data *data) {
    if(data == nullptr) {
        return;
    }
    switch(data->getType()) {
        case DataType::VOTE:
            processVote(data);
            break;
        case DataType::MUSIC_FILE:
            processMusicFile(data);
            break;
        case DataType::CONNECTION:
            processConnectionMessage(data);
            break;
        case DataType::STREAM:
            wrongDataType();
    }
}

void Dispatcher::processVote(Data *data) {
    logger->log("Processing - data type VOTE");
}

void Dispatcher::processMusicFile(Data *data) {
    logger->log("Processing - data type MUSIC_FILE");
}

void Dispatcher::processConnectionMessage(Data *data) {
    logger->log("Processing - data type CONNECTION");
}

void Dispatcher::wrongDataType() {
    logger->log("Processing - wrong data type");
}







