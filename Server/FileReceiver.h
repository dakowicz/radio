//
// Created by tomasz on 28.05.16.
//

#ifndef SERVER_FILERECEIVER_H
#define SERVER_FILERECEIVER_H


#include <iostream>
#include <memory>
#include "FileManager.h"

class FileReceiver {

public:

    FileReceiver(std::shared_ptr<FileManager> fileManager);

private:

    std::shared_ptr<FileManager> fileManager;
};


#endif //SERVER_FILERECEIVER_H
