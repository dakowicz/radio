//
// Created by tomasz on 28.05.16.
//

#ifndef SERVER_FILEMANAGER_H
#define SERVER_FILEMANAGER_H


#include <fstream>

class FileManager {

public:

    std::shared_ptr<std::ifstream> getFileStream();

    static std::string PREFIX;

private:
};


#endif //SERVER_FILEMANAGER_H
