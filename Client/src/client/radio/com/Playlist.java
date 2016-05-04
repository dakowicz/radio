package client.radio.com;

import java.util.HashSet;
import java.util.List;
import java.util.Set;

/**
 * Created by Michał on 2016-04-23.
 */
public class Playlist {

    private Set<Song> playlist;

    public Playlist() {
        playlist = new HashSet<Song>();
    }

    public Set<Song> getPlaylist() {
        return playlist;
    }

    public void setPlaylist(Set<Song> playlist) {
        this.playlist = playlist;
    }

    public void vote(int songId) {

    }
}
