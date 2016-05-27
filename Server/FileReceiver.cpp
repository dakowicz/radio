//
// Created by tomasz on 28.05.16.
//

#include <iostream>
#include "FileReceiver.h"

FileReceiver::FileReceiver(std::shared_ptr<FileManager> fileManager) {
    this->fileManager = fileManager;
}
