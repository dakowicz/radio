//
// Created by tomasz on 28.05.16.
//

#include "PlaylistManager.h"

std::string PlaylistManager::MODULE_NAME = "PlaylistManager";

std::shared_ptr<Song> PlaylistManager::getCurrentSong() {
    std::shared_ptr<Song> currentSong = songs[currentPosition];
    moveIterator();
    return currentSong;
}

void PlaylistManager::moveIterator() {
    currentPosition++;
    currentPosition %= songs.size();
}

void PlaylistManager::loadPlaylist() {
//    while(!playlistFileReader->endOF()) {
        std::shared_ptr<Song> song = playlistFileReader.getNextRow();
        addSong(song);
//    }
}

void PlaylistManager::addSong(std::shared_ptr<Song> song) {
    songs.push_back(song);
}
