//
// Created by tomasz on 28.05.16.
//


#include "Song.h"


Song::Song(std::string fileName, std::string title, std::string author) {
    this->fileName = fileName;
    this->title = title;
    this->author = author;
}

Song::~Song() {

}


