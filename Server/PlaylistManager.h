//
// Created by tomasz on 28.05.16.
//

#ifndef SERVER_PLAYLISTMANAGER_H
#define SERVER_PLAYLISTMANAGER_H


#include <vector>
#include "AtomicQueue.h"
#include "PlaylistFileReader.h"
#include "SongList.h"
#include "VoteType.h"
#include "Data.h"

class PlaylistManager {

public:

    PlaylistManager(std::string &prefix) :
            playlistFileReader(prefix), logger(MODULE_NAME) {
        loadPlaylist();
        addVote(0);
        addVote(2);
        addVote(2);
        addVote(3);
        addVote(3);
        addVote(3);
    }

    std::shared_ptr<Song> getCurrentSong();

    void addVote(int songID);

    void subtractVote(int songID);

    void getPlaylistCSV(std::string &content);

private:

    SongList songs;

    PlaylistFileReader playlistFileReader;

    Logger logger;

    static std::string MODULE_NAME;

    void loadPlaylist();

    void addSong(std::shared_ptr<Song> song);

    void writeSongs(std::string &content);

    void writeCSVHeader(std::string &content);
};


#endif //SERVER_PLAYLISTMANAGER_H
