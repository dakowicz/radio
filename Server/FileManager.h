//
// Created by tomasz on 28.05.16.
//

#ifndef SERVER_FILEMANAGER_H
#define SERVER_FILEMANAGER_H


#include <fstream>
#include "Song.h"
#include "Logger.h"

class FileManager {

public:

    FileManager(std::string &prefix);

    ~FileManager();

    std::shared_ptr<std::ifstream> getFileStream(Song *song);

private:

    std::string prefix;

    Logger *logger;

    static std::string MODULE_NAME;
};


#endif //SERVER_FILEMANAGER_H
