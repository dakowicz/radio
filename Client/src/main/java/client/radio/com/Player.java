package client.radio.com;


import javafx.application.Application;
import javafx.concurrent.Task;
import javafx.scene.media.Media;
import javafx.scene.media.MediaPlayer;
import javafx.stage.Stage;
import lombok.Data;
import lombok.extern.slf4j.Slf4j;

import java.io.File;
import java.io.FileInputStream;

/**
 * Created by Michał on 2016-04-23.
 */

@Data
@Slf4j
public class Player extends Task<Void> {
    private Media sound;
    private File stream;
    private MediaPlayer mediaPlayer;

    public Player(Media sound, File stream, MediaPlayer mediaPlayer){
        this.sound = sound;
        this.stream = stream;
        this.mediaPlayer = mediaPlayer;
    }

    @Override
    protected Void call() throws Exception {
        while (stream == null || stream.length() <= 0) {
            stream = new File("songStream.mp3");
        }
        if (sound == null) {
            sound = new Media(new File("songStream.mp3").toURI().toString());
        }
        if (mediaPlayer == null) {
            mediaPlayer = new MediaPlayer(sound);
        }
        mediaPlayer.play();
        return null;
    }

    public void mute() {

    }

    public void unmute() {
    }
}
