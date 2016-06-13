#include "Dispatcher.h"


std::string Dispatcher::MODULE_NAME = "Dispatcher";

void Dispatcher::start() {
    std::shared_ptr<Data> newMessage;
    this->running = true;
    while(isRunning()) {
        newMessage = atomicQueue.pop();
        processMessage(newMessage);
    }
}

void Dispatcher::addMessage(std::shared_ptr<Data> newMessage) {
    if(isMessageEmpty(newMessage)) {
        return;
    }
    atomicQueue.push(newMessage);
}

bool Dispatcher::isMessageEmpty(std::shared_ptr<Data> newMessage) const {
    return newMessage == nullptr || newMessage->getContent() == nullptr;
}

void Dispatcher::processMessage(std::shared_ptr<Data> data) {
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

void Dispatcher::processVote(std::shared_ptr<Data> data) {
    logger.log("Processing - data type VOTE");
    switch (data->getParameters()){
        case (char) VoteType::ADD:
            playlistManager.addVote(getSongID(data));
            break;
        case (char) VoteType::SUBTRACT:
            playlistManager.subtractVote(getSongID(data));
            break;
    }
    broadcastPlaylist();
}

int Dispatcher::getSongID(std::shared_ptr<Data> data) const {
    const char *content = data->getContent();
    int songID = content[0] << 24;
    songID += content[1] << 16;
    songID += content[2] << 8;
    songID += content[3];
    return songID;
}

void Dispatcher::processMusicFile(std::shared_ptr<Data> data) {
    logger.log("Processing - data type MUSIC_FILE");
    std::string newFileName;
    switch (data->getParameters()){
        case (char) FileType::MUSIC:
            std::string author, title;
            getSongData(data, author, title);
            newFileName = addNewMusicFile(data, author, title);
            playlistManager.addSong(newFileName, author, title);
    }
}

std::string Dispatcher::addNewMusicFile(const std::shared_ptr<Data> &data, const std::string &author, const std::string &title) const {
    return fileManager.addMusicFile(data->getContent(), data->getSize(), author, title);
}

void Dispatcher::processConnectionMessage(std::shared_ptr<Data> data) {
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

void Dispatcher::getSongData(std::shared_ptr<Data> &data, std::string &author, std::string &title) {
    int songDataSize = data->getParameters();
    std::string songData(data->getContent(), songDataSize);
    author = songData.substr(0, songData.find('|'));
    title = songData.substr(songData.find('|') + 1, songData.size() - author.size() -1);
}






