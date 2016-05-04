package client.radio.com;

/**
 * Created by Michał on 2016-04-23.
 */
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

    public int getVotesNumber() {
        return votesNumber;
    }

    public void setVotesNumber(int votesNumber) {
        this.votesNumber = votesNumber;
    }

    public String getBand() {
        return band;
    }

    public void setBand(String band) {
        this.band = band;
    }

    public String getTitle() {
        return title;
    }

    public void setTitle(String title) {
        this.title = title;
    }
    public void addVote(){
        votesNumber++;
    }
    public void subtractVote(){
        votesNumber--;
    }

    public boolean isVoted() {
        return isVoted;
    }

    public void setVoted(boolean voted) {
        isVoted = voted;
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }
}
