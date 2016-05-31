//
// Created by tomasz on 28.05.16.
//

#include <memory>
#include <iostream>
#include "FileManager.h"

std::string FileManager::MODULE_NAME = "FileManager";

FileManager::FileManager(std::string &prefix) {
    this->prefix = prefix;
    this->logger = new Logger(MODULE_NAME);
}

FileManager::~FileManager() {
    delete logger;
}

std::shared_ptr<std::ifstream> FileManager::getFileStream(Song *song) {
    std::shared_ptr<std::ifstream> fileStream = std::make_shared<std::ifstream>();
    fileStream->open(prefix + song->getFileName());
    return fileStream;
}





