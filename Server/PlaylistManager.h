//
// Created by tomasz on 28.05.16.
//

#ifndef SERVER_PLAYLISTMANAGER_H
#define SERVER_PLAYLISTMANAGER_H


#include "Song.h"
#include "ClientManager.h"

class PlaylistManager {

public:

    PlaylistManager();

    Song *getNextSong();

private:

};


#endif //SERVER_PLAYLISTMANAGER_H
