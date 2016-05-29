//
// Created by tomasz on 28.05.16.
//

#ifndef SERVER_SONG_H
#define SERVER_SONG_H

#include <string>

class Song {
public:

    Song(std::string name);

    const std::string &getName() const { return name; }

private:
    std::string name;
};


#endif //SERVER_SONG_H
