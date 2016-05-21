package client.radio.com;

import lombok.Data;

/**
 * Created by Michał on 2016-04-23.
 */

@Data
public class Song {

    private String title;
    private String band;
    private int id;
    private int votesNumber;
    private boolean isVoted;

    public Song(String title, String band, int id, int votesNumber) {
        this.title = title;
        this.band = band;
        this.id = id;
        this.votesNumber = votesNumber;
        this.isVoted = false;
    }
}
