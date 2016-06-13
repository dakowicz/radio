//
// Created by tomasz on 29.05.16.
//

#include "PlaylistFileReader.h"

std::string PlaylistFileReader::MODULE_NAME = "PlaylistFileReader";

std::string PlaylistFileReader::FILE_NAME = "playlist.csv";

std::string PlaylistFileReader::FILENAME_COLUMN("fileName");

std::string PlaylistFileReader::TITLE_COLUMN("title");

std::string PlaylistFileReader::AUTHOR_COLUMN("author");

const char PlaylistFileReader::DELIM = '|';

bool PlaylistFileReader::endOF() {
    return fileStream.eof();
}

std::shared_ptr<Song> PlaylistFileReader::getNextRow() {
    std::string fileName, title, author;
    getRow(fileName, title, author);
    return std::make_shared<Song>(fileName, title, author);
}

void PlaylistFileReader::readHeader() {
    std::string fileName, title, author;
    getRow(fileName, title, author);
    if(fileName != FILENAME_COLUMN || title != TITLE_COLUMN || author != AUTHOR_COLUMN){
        throw std::invalid_argument("Wrong header of CSV file");
    }
}

void PlaylistFileReader::getRow(std::string &fileName, std::string &title, std::string &author) {
    std::getline(fileStream, fileName, DELIM);
    std::getline(fileStream, title, DELIM);
    std::getline(fileStream, author, '\n');
}













