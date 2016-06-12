//
// Created by tomasz on 28.05.16.
//

#ifndef SERVER_PLAYLISTMANAGER_H
#define SERVER_PLAYLISTMANAGER_H


#include <vector>
#include "Song.h"
#include "AtomicQueue.h"
#include "PlaylistFileReader.h"

class PlaylistManager {

public:

    PlaylistManager(std::string &prefix) : currentPosition(0), playlistFileReader(prefix), logger(MODULE_NAME) {
        loadPlaylist();
    }

    std::shared_ptr<Song> getCurrentSong();

private:

    std::vector<std::shared_ptr<Song>> songs;

    std::vector<Song *>::iterator currentSong;

    PlaylistFileReader playlistFileReader;

    Logger logger;

    static std::string MODULE_NAME;

    static std::string PLAYLIST_FILENAME;

    void loadPlaylist();

    void addSong(std::shared_ptr<Song> song);

    void moveIterator();

    int currentPosition;
};


#endif //SERVER_PLAYLISTMANAGER_H
