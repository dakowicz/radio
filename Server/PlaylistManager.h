//
// Created by tomasz on 28.05.16.
//

#ifndef SERVER_PLAYLISTMANAGER_H
#define SERVER_PLAYLISTMANAGER_H


#include "Song.h"
#include "ClientManager.h"
#include "PlaylistFileReader.h"

class PlaylistManager {

public:

    PlaylistManager(std::string prefix);

    ~PlaylistManager();

    Song *getNextSong();

    void popRecording(Song *&song);

private:

    std::vector<Song *> songs;

    std::vector<Song *>::iterator currentSong;

    AtomicQueue<Song *> *recordings;

    static std::string MODULE_NAME;

    void loadPlaylist();

    static std::string PLAYLIST_FILENAME;

    PlaylistFileReader *playlistFileReader;

    void addSong(Song *song);

    void moveIterator();

    void addRecording(Song *recording);
};


#endif //SERVER_PLAYLISTMANAGER_H
