//
// Created by tomasz on 29.05.16.
//

#ifndef SERVER_PLAYLISTFILEREADER_H
#define SERVER_PLAYLISTFILEREADER_H

#include <string>
#include <memory>
#include <fstream>
#include "Song.h"

class PlaylistFileReader {
public:

    PlaylistFileReader(std::string prefix);

    bool endOF();

    std::shared_ptr<Song> getNextRow();

private:

    std::string prefix;

    void readHeader();

    std::ifstream *fileStream;

    static std::string FILE_NAME;

    static std::string MODULE_NAME;
};


#endif //SERVER_PLAYLISTFILEREADER_H
