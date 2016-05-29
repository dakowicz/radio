//
// Created by tomasz on 28.05.16.
//

#ifndef SERVER_SONG_H
#define SERVER_SONG_H

#include <string>

class Song {
public:

    Song(std::string fileName, std::string title, std::string author);

    ~Song();

    const std::string &getTitle() const { return title; }

    const std::string &getAuthor() const { return author; }

    const std::string &getFileName() const { return fileName; }

private:

    std::string title;

    std::string author;

    std::string fileName;
};


#endif //SERVER_SONG_H
