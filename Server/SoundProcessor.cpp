//
// Created by tomasz on 28.05.16.
//

#include "SoundProcessor.h"

std::string SoundProcessor::MODULE_NAME = "SoundProcessor";

std::chrono::milliseconds SoundProcessor::TIME_INTERVAL_MS(1000);

int SoundProcessor::PACKAGE_SIZE_B = 200000;

int SoundProcessor::ID_SIZE = 4;

void SoundProcessor::stream() {
    this->running = true;
    while(isRunning()) {
        std::shared_ptr<Song> currentSong = playlistManager.getCurrentSong();
        std::shared_ptr<std::ifstream> fileStream = fileManager.getFileStream(currentSong);
        divideFile(fileStream, currentSong->getID());
    }
}

void SoundProcessor::divideFile(std::shared_ptr<std::ifstream> fileStream, int songID) {
    if(fileStream == nullptr) {
        logger.log("Opening file error");
        return;
    }
    while(!endOf(fileStream) && isRunning()) {
        sleep();
        pushStreamData(fileStream, songID);
        logger.log("New package of data");
    }
}

void SoundProcessor::pushStreamData(std::shared_ptr<std::ifstream> fileStream, int songID) {
    logger.log("Position in current file: " + std::to_string(fileStream->tellg()));
    Data *data = readFile(fileStream, songID);
    broadcastToClients(data);
}

Data * SoundProcessor::readFile(std::shared_ptr<std::ifstream> fileStream, int songID) {
    char *streamData = new char[ID_SIZE + PACKAGE_SIZE_B];
    saveSongID(streamData, songID);
    fileStream->read(streamData + ID_SIZE, PACKAGE_SIZE_B);
    return new Data(DataType::STREAM, streamData, (int) fileStream->gcount() + ID_SIZE);
}

void SoundProcessor::broadcastToClients(Data *data) {
    std::vector<int> sockets;
    clients->getAllKeys(sockets);
    for(auto &socket: sockets) {
        ClientManager* clientManager = clients->get(socket);
        if(clientManager != nullptr) {
            clientManager->send(data);
        }
    }
}

void SoundProcessor::saveSongID(char *streamData, int songID) {
    streamData[0] = (char) (songID >> 24);
    streamData[1] = (char) (songID >> 16);
    streamData[2] = (char) (songID >> 8);
    streamData[3] = (char) songID;
}

void SoundProcessor::sleep() const { std::this_thread::sleep_for(TIME_INTERVAL_MS); }

bool SoundProcessor::endOf(std::shared_ptr<std::ifstream> fileStream) const { return fileStream->eof(); }




