package client.radio.com;


import javafx.application.Application;
import javafx.scene.media.Media;
import javafx.scene.media.MediaPlayer;
import javafx.stage.Stage;

import javax.sound.sampled.AudioFormat;
import javax.sound.sampled.AudioInputStream;
import java.io.FileInputStream;

/**
 * Created by Michał on 2016-04-23.
 */
public class Player extends Application {
    private FileInputStream inputStreamFile;
    private Media sound;
    private MediaPlayer mediaPlayer;
    private Song currentSong;




    @Override
    public void start(Stage primaryStage) throws Exception {

    }


    public FileInputStream getInputStreamFile() {
        return inputStreamFile;
    }

    public void setInputStreamFile(FileInputStream inputStreamFile) {
        this.inputStreamFile = inputStreamFile;
    }
    public void mute(){

    }
    public void unmute(){}

    public Song getCurrentSong() {
        return currentSong;
    }

    public void setCurrentSong(Song currentSong) {
        this.currentSong = currentSong;
    }
}
