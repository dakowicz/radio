//
// Created by tomasz on 28.05.16.
//

#include "PlaylistManager.h"

PlaylistManager::PlaylistManager() {

}

Song *PlaylistManager::getNextSong() {
    return new Song("musicFile");
}
