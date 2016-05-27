//
// Created by tomasz on 28.05.16.
//

#include <memory>
#include <iostream>
#include "FileManager.h"

std::string FileManager::PREFIX = "/home/tomasz/prog/radio/Server/";

std::shared_ptr<std::ifstream> FileManager::getFileStream() {
    std::shared_ptr<std::ifstream> fileStream = std::make_shared<std::ifstream>();
    fileStream->open(PREFIX + "musicFile");
    return fileStream;
}

