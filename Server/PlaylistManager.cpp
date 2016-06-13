//
// Created by tomasz on 28.05.16.
//

#include <cstring>
#include "PlaylistManager.h"

std::string PlaylistManager::MODULE_NAME = "PlaylistManager";

std::shared_ptr<Song> PlaylistManager::getCurrentSong() {
    return songs.getFirst();
}

void PlaylistManager::loadPlaylist() {
    while(!playlistFileReader.endOF()) {
        std::shared_ptr<Song> song = playlistFileReader.getNextRow();
        addSong(song);
    }
}

bool PlaylistManager::isCorrect(const std::shared_ptr<Song> &song) const { return !song->getFileName().empty(); }

void PlaylistManager::addSong(std::shared_ptr<Song> song) {
    songs.add(song);
}

void PlaylistManager::addSong(std::string fileName, std::string author, std::string title) {
    std::shared_ptr<Song> song = std::make_shared<Song>(fileName, title, author);
    songs.add(song);
    playlistFileReader.addToPlaylistFile(song);
}

void PlaylistManager::addVote(int songID) {
    songs.addVote(songID);
}

void PlaylistManager::subtractVote(int songID) {
    songs.subtractVote(songID);
}

void PlaylistManager::getPlaylistCSV(std::string &content) {
    writeCSVHeader(content);
    writeSongs(content);
    logger.log(content);
}

void PlaylistManager::writeCSVHeader(std::string &content) {
    std::string csvHeader = "ID|title|author|votes\n";
    content += csvHeader;
}

void PlaylistManager::writeSongs(std::string &content) {
    songs.writeSongs(content);
}













