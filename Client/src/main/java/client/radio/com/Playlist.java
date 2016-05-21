package client.radio.com;

import lombok.Data;
import java.util.HashSet;
import java.util.Set;

/**
 * Created by Michał on 2016-04-23.
 */

@Data
public class Playlist {

    private Set<Song> playlist;

    public Playlist() {
        playlist = new HashSet<Song>();
    }

    public void vote(int songId) {

    }
}
