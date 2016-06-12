//
// Created by tomasz on 28.05.16.
//

#ifndef SERVER_SONG_H
#define SERVER_SONG_H

#include <string>
#include <atomic>

class Song {
public:

    Song(std::string fileName, std::string title, std::string author);

    const std::string &getTitle() const { return title; }

    const std::string &getAuthor() const { return author; }

    const std::string &getFileName() const { return fileName; }

    int getID();

    void resetVotes();

    int getVotes() const { return votes; }

    bool operator<(const Song &other);

private:

    std::string title;

    std::string author;

    std::string fileName;

    int ID;

    static std::atomic<int> GLOBAL_ID;

    int votes;
};


#endif //SERVER_SONG_H
