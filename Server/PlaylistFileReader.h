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

    PlaylistFileReader(std::string prefix) : prefix(prefix), fileStream(prefix + FILE_NAME) {
        readHeader();
    };

    bool endOF();

    std::shared_ptr<Song> getNextRow();

    void addToPlaylistFile(std::shared_ptr<Song> song);

private:

    void readHeader();

    std::string prefix;

    std::ifstream fileStream;

    static std::string FILE_NAME;

    static std::string MODULE_NAME;

    static const char DELIM;

    static std::string FILENAME_COLUMN;

    static std::string TITLE_COLUMN;

    static std::string AUTHOR_COLUMN;

    void getRow(std::string &fileName, std::string &title, std::string &author);
};


#endif //SERVER_PLAYLISTFILEREADER_H
