//
// Created by tomasz on 28.05.16.
//

#include <memory>
#include <iostream>
#include "FileManager.h"
#include "Song.h"

FileManager::FileManager(std::string &prefix) {
    this->prefix = prefix;
}

std::shared_ptr<std::ifstream> FileManager::getFileStream(Song *song) {
    std::shared_ptr<std::ifstream> fileStream = std::make_shared<std::ifstream>();
    fileStream->open(prefix + song->getName());
    return fileStream;
}



