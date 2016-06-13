#include "Dispatcher.h"


std::string Dispatcher::MODULE_NAME = "Dispatcher";

void Dispatcher::start() {
    Data *newMessage;
    this->running = true;
    while(isRunning()) {
        newMessage = atomicQueue.pop();
        processMessage(newMessage);
    }
}

void Dispatcher::addMessage(Data *newMessage) {
    if(isMessageEmpty(newMessage)) {
        return;
    }
    atomicQueue.push(newMessage);
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
        case DataType::CLOSED:break;
    }
}

void Dispatcher::processVote(Data *data) {
    logger.log("Processing - data type VOTE");
    int songID = getSongID(data);
    switch (data->getParameters()){
        case (char) VoteType::ADD:
            playlistManager.addVote(songID);
            break;
        case (char) VoteType::SUBTRACT:
            playlistManager.subtractVote(songID);
            break;
    }
    broadcastPlaylist();
}

int Dispatcher::getSongID(const Data *data) const {
    const char *content = data->getContent();
    int songID = content[0] << 24;
    songID += content[1] << 16;
    songID += content[2] << 8;
    songID += content[3];
    return songID;
}

void Dispatcher::processMusicFile(Data *data) {
    logger.log("Processing - data type MUSIC_FILE");
}

void Dispatcher::processConnectionMessage(Data *data) {
    logger.log("Processing - data type CONNECTION");
}

void Dispatcher::wrongDataType() {
    logger.log("Processing - wrong data type");
}

void Dispatcher::broadcastPlaylist() {
    std::string playlistContent;
    getPlaylistCSV(playlistContent);
    char* content = new char[playlistContent.size()];
    std::copy(playlistContent.begin(), playlistContent.end(), content);
    std::shared_ptr<Data> playlist = std::make_shared<Data>(DataType::VOTE, content, playlistContent.size(), (char) VoteType::TO_CLIENT);
    clients->broadcast(playlist);
}

void Dispatcher::getPlaylistCSV(std::string &content) {
    playlistManager.getPlaylistCSV(content);
}
