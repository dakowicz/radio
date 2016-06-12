//
// Created by tomasz on 28.05.16.
//

#include "FileManager.h"

std::string FileManager::MODULE_NAME = "FileManager";

std::shared_ptr<std::ifstream> FileManager::getFileStream(std::shared_ptr<Song> song) {
    std::shared_ptr<std::ifstream> fileStream = std::make_shared<std::ifstream>();
    fileStream->open(prefix + song->getFileName());
    return fileStream;
}