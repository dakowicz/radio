//
// Created by tomasz on 28.05.16.
//


#include "Song.h"

std::atomic<int> Song::GLOBAL_ID(0);

Song::Song(std::string fileName, std::string title, std::string author) {
    this->fileName = fileName;
    this->title = title;
    this->author = author;
    this->ID = GLOBAL_ID++;
    this->votes = 0;
}

int Song::getID() {
    return ID;
}

void Song::resetVotes() {
    votes = 0;
}

void Song::addVote() {
    votes++;
}

void Song::subtractVote() {
    votes--;
}










