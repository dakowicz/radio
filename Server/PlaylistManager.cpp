//
// Created by tomasz on 28.05.16.
//

#include "PlaylistManager.h"

std::string PlaylistManager::MODULE_NAME = "PlaylistManager";

std::string PlaylistManager::PLAYLIST_FILENAME = "playlist.csv";

Song *PlaylistManager::getNextSong() {
    Song *nextSong = *currentSong;
    moveIterator();
    return nextSong;
}

void PlaylistManager::moveIterator() {
    if(currentSong != songs.end()) {
        currentSong++;
    } else {
        currentSong = songs.begin();
    }
}

void PlaylistManager::loadPlaylist() {
//    while(!playlistFileReader->endOF()) {
        Song *song = playlistFileReader.getNextRow();
        addSong(song);
//    }
}

void PlaylistManager::addSong(Song *song) {
    songs.push_back(song);
    if(songs.size() == 1) {
        currentSong = songs.begin();
    }
}

void PlaylistManager::addRecording(Song *recording) {
    recordings.push(recording);
}

void PlaylistManager::popRecording(Song *&song) {
    recordings.pop(song);
}