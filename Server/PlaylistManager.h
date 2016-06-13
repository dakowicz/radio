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

    PlaylistManager(std::string &prefix) : playlistFileReader(prefix), logger(MODULE_NAME) {
        loadPlaylist();
    }

    std::shared_ptr<Song> getCurrentSong();

    void addVote(int songID);

    void subtractVote(int songID);

    void getPlaylistCSV(std::string &content);

    void addSong(std::shared_ptr<Song> song);

    void addSong(std::string fileName, std::string author, std::string title);

private:

    SongList songs;

    PlaylistFileReader playlistFileReader;

    Logger logger;

    static std::string MODULE_NAME;

    void loadPlaylist();

    void writeSongs(std::string &content);

    void writeCSVHeader(std::string &content);
};


#endif //SERVER_PLAYLISTMANAGER_H
