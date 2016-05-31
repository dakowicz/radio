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

    PlaylistManager(std::string &prefix) : recordings(MODULE_NAME + "Recordings"), playlistFileReader(prefix), logger(MODULE_NAME) {
        loadPlaylist();
    }

    Song *getNextSong();

    void popRecording(Song *&song);

private:

    std::vector<Song *> songs;

    std::vector<Song *>::iterator currentSong;

    AtomicQueue<Song *> recordings;

    PlaylistFileReader playlistFileReader;

    Logger logger;

    static std::string MODULE_NAME;

    static std::string PLAYLIST_FILENAME;

    void loadPlaylist();

    void addSong(Song *song);

    void moveIterator();

    void addRecording(Song *recording);
};


#endif //SERVER_PLAYLISTMANAGER_H
