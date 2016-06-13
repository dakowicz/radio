//
// Created by tomasz on 28.05.16.
//

#ifndef SERVER_FILEMANAGER_H
#define SERVER_FILEMANAGER_H


#include <fstream>
#include <memory>
#include "Song.h"
#include "Logger.h"

class FileManager {
public:

    FileManager(std::string &prefix) : prefix(prefix), logger(MODULE_NAME) {}

    std::shared_ptr<std::ifstream> getFileStream(std::shared_ptr<Song> song);

    std::string addMusicFile(const char *content, int size, std::string author, std::string title);

private:

    std::string &prefix;

    Logger logger;

    static std::string MODULE_NAME;

    void saveNewFile(const char *content, int size, const std::string &author, const std::string &title,
                     const std::string &fileName) const;
};


#endif //SERVER_FILEMANAGER_H
