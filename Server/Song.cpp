//
// Created by tomasz on 28.05.16.
//


#include "Song.h"

int Song::globalID = 0;

Song::Song(std::string fileName, std::string title, std::string author) {
    this->fileName = fileName;
    this->title = title;
    this->author = author;
    this->ID = globalID++;
}

Song::~Song() {

}

int Song::getID() {
    return ID;
}





