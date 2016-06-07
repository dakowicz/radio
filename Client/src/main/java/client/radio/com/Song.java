package client.radio.com;

import lombok.Data;
import lombok.extern.slf4j.Slf4j;

/**
 * Created by Michał on 2016-04-23.
 */

@Data
@Slf4j
public class Song {

    private String title;
    private String band;
    private int id;
    private int votesNumber;
    private boolean isVoted;
    private boolean isPlayed;
    private boolean isStreamed;
    private String fileName;

    public Song(String title, String band, int id, int votesNumber) {
        this.title = title;
        this.band = band;
        this.id = id;
        this.votesNumber = votesNumber;
        this.isVoted = false;
        this.isStreamed = false;
        this.isPlayed = false;

    }

    public void incVotesNumber(){
        votesNumber++;
    }
    public void decVotesNumber(){
        votesNumber--;
    }
}
