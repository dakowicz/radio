//
// Created by tomasz on 29.05.16.
//

#include "PlaylistFileReader.h"

std::string PlaylistFileReader::MODULE_NAME = "PlaylistFileReader";

std::string PlaylistFileReader::FILE_NAME = "playlist.csv";

PlaylistFileReader::PlaylistFileReader(std::string prefix) {
    this->prefix = prefix;
    this->fileStream = new std::ifstream(prefix + FILE_NAME);
    readHeader();
}

bool PlaylistFileReader::endOF() {
    return fileStream->eof();
}

Song *PlaylistFileReader::getNextRow() {
    return new Song("musicFile", "title", "author");
}

void PlaylistFileReader::readHeader() {
}












