//
// Created by tomasz on 12.06.16.
//

#include <iostream>
#include "SongList.h"

std::shared_ptr<Song> SongList::getFirst() {
    std::unique_lock<std::shared_timed_mutex> lock(mutex);
    std::shared_ptr<Song> first = songs.front();
    resetPosition(first);
    lock.unlock();
    return first;
}

void SongList::resetPosition(std::shared_ptr<Song> &first) {
    songs.pop_front();
    first->resetVotes();
    songs.push_back(first);
}

void SongList::add(std::shared_ptr<Song> song) {
    std::unique_lock<std::shared_timed_mutex> lock(mutex);
    songs.push_back(song);
    lock.unlock();
}

void SongList::addVote(int songID) {
    std::unique_lock<std::shared_timed_mutex> lock(mutex);
    std::shared_ptr<Song> song = findSong(songID);
    song->addVote();
    updateOrder();
    lock.unlock();
}

void SongList::subtractVote(int songID) {
    std::unique_lock<std::shared_timed_mutex> lock(mutex);
    std::shared_ptr<Song> song = findSong(songID);
    song->subtractVote();
    updateOrder();
    lock.unlock();
}

std::shared_ptr<Song> SongList::findSong(int songID) const {
    for(auto& song : songs){
        if(songID == song->getID()){
            return song;
        }
    }
    return nullptr;
}

void SongList::updateOrder() { songs.sort([](std::shared_ptr<Song> a, std::shared_ptr<Song> b){return a->getVotes() > b->getVotes();}); }

void SongList::writeSongs(std::string &content) {
    std::shared_lock<std::shared_timed_mutex> lock(mutex);
    for(auto& song : songs){
        content += std::to_string(song->getID());
        content += '|';
        content += song->getTitle();
        content += '|';
        content += song->getAuthor();
        content += '|';
        content += std::to_string(song->getVotes());
        content += '\n';
    }
}















