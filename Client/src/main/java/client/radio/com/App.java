package client.radio.com;

import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.layout.StackPane;
import javafx.scene.media.Media;
import javafx.scene.media.MediaPlayer;
import javafx.stage.Stage;
import lombok.Data;
import lombok.extern.slf4j.Slf4j;

import java.io.File;

/**
 * Created by Michał on 2016-04-23.
 */

@Slf4j
@Data
public class App extends Application implements Runnable {
    private StreamPlayer streamPlayer;
    private Receiver receiver;
    private Playlist playlist;
    private Sender sender;
    private Recorder recorder;
    private Controller controller;
    private Media sound;
    private MediaPlayer mediaPlayer;
    private Song currentSong;
    private File stream;


    @Override
    public void start(Stage primaryStage) throws Exception {
        primaryStage.setTitle("Radio");
        final Button playButton = new Button("Play");
        playButton.setOnAction( event -> {
            if (mediaPlayer != null && mediaPlayer.getStatus() == MediaPlayer.Status.PLAYING) {
                stopPlayer();
                playButton.setText("Start");
            } else {
                startPlayer();
                playButton.setText("Pause");
            }
        });

        StackPane root = new StackPane();
        root.getChildren().add(playButton);
        primaryStage.setScene(new Scene(root, 600, 400));
        primaryStage.show();
    }

    @Override
    public void stop() throws Exception {
        super.stop();
        System.exit(0);
    }

    public void run() {
        launch(this.getClass());
    }

    public void startPlayer() {
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
    }

    public void stopPlayer() {
        log.info("stop");
        if (mediaPlayer != null) {
            mediaPlayer.pause();
        }
    }
}
