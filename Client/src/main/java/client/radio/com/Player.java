package client.radio.com;


import javafx.application.Application;
import javafx.scene.media.Media;
import javafx.scene.media.MediaPlayer;
import javafx.stage.Stage;
import lombok.Data;
import java.io.FileInputStream;

/**
 * Created by Michał on 2016-04-23.
 */

@Data
public class Player extends Application {
    private FileInputStream inputStreamFile;
    private Media sound;
    private MediaPlayer mediaPlayer;
    private Song currentSong;


    @Override
    public void start(Stage primaryStage) throws Exception {

    }

    public void mute() {

    }

    public void unmute() {
    }
}
