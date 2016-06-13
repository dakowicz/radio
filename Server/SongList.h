//
// Created by tomasz on 12.06.16.
//

#ifndef SERVER_SONGVECTOR_H
#define SERVER_SONGVECTOR_H


#include <list>
#include <memory>
#include <algorithm>
#include <functional>
#include <shared_mutex>
#include "Song.h"

class SongList {
public:

    std::shared_ptr<Song> getFirst();

    void add(std::shared_ptr<Song> song);

    void addVote(int songID);

    void subtractVote(int songID);

    void getAll(std::vector<std::shared_ptr<Song>> &vector);

    void writeSongs(std::string &content);

private:

    std::list<std::shared_ptr<Song>> songs;

    std::shared_timed_mutex mutex;

    void resetPosition(std::shared_ptr<Song> &first);

    std::shared_ptr<Song> findSong(int songID) const;

    void updateOrder();

    static bool comparator(std::shared_ptr<Song> first, std::shared_ptr<Song> second);

    void printAll();
};


#endif //SERVER_SONGVECTOR_H
