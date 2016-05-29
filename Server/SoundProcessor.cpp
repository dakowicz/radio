//
// Created by tomasz on 28.05.16.
//

#include <fstream>
#include <cstring>
#include "SoundProcessor.h"

std::string SoundProcessor::MODULE_NAME = "SoundProcessor";

std::chrono::milliseconds SoundProcessor::TIME_INTERVAL_MS(1000);

int SoundProcessor::PACKAGE_SIZE_B = 200000;

SoundProcessor::SoundProcessor(const std::shared_ptr<FileManager> &fileManager,
                               const std::shared_ptr<PlaylistManager> &playlistManager,
                               const std::shared_ptr<AtomicMap<int, ClientManager * > > &clients) {
    this->clients = clients;
    this->fileManager = fileManager;
    this->playlistManager = playlistManager;
}

void SoundProcessor::stream() {
    this->running = true;
    while(isRunning()) {
        Song *nextSong = playlistManager->getNextSong();
        std::shared_ptr<std::ifstream> fileStream = fileManager->getFileStream(nextSong);
        divideFile(fileStream);
    }
}

void SoundProcessor::divideFile(std::shared_ptr<std::ifstream> fileStream) {
    if(fileStream == nullptr) {
        return;
    }
    while(!endOf(fileStream)) {
        std::this_thread::sleep_for(TIME_INTERVAL_MS);
        pushStreamMessage(fileStream);
        log("New package of data");
    }
}

bool SoundProcessor::endOf(std::shared_ptr<std::ifstream> fileStream) const { return fileStream->eof(); }

void SoundProcessor::pushStreamMessage(std::shared_ptr<std::ifstream> fileStream) {
    log("Position in current file: " + std::to_string(fileStream->tellg()));
    unsigned char *streamData = new unsigned char[PACKAGE_SIZE_B];
    Data *data = readFile(fileStream, streamData);
    broadcastToClients(data);
}

Data *SoundProcessor::readFile(std::shared_ptr<std::ifstream> &fileStream, unsigned char *streamData) const {
    fileStream->read((char *) streamData, PACKAGE_SIZE_B);
    return new Data(DataType::STREAM, streamData, (int) fileStream->gcount());
}

void SoundProcessor::broadcastToClients(Data *data) {
    std::vector<ClientManager *> clientManagers;
    clients->getAllValues(clientManagers);
    for(auto &clientManager: clientManagers) {
        if(clientManager != nullptr) {
            clientManager->send(data);
        }
    }
}

void SoundProcessor::log(std::string message) {
    std::cout << MODULE_NAME << ": " << message << std::endl << std::flush;
}





