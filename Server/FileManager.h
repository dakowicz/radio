//
// Created by tomasz on 28.05.16.
//

#ifndef SERVER_FILEMANAGER_H
#define SERVER_FILEMANAGER_H


#include <fstream>
#include "Song.h"

class FileManager {

public:

    FileManager(std::string &prefix);

    std::shared_ptr<std::ifstream> getFileStream(Song *song);

private:

    std::string prefix;
};


#endif //SERVER_FILEMANAGER_H
