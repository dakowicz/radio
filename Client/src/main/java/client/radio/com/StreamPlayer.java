package client.radio.com;


import javazoom.jl.player.Player;
import lombok.Data;
import lombok.extern.slf4j.Slf4j;

import javax.sound.sampled.*;
import java.io.*;
import java.util.LinkedList;
import java.util.List;
import java.util.Stack;
import java.util.Vector;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;

/**
 * Created by Michał on 2016-04-23.
 */

@Data
@Slf4j
public class StreamPlayer implements Runnable {
    private BlockingQueue<String> streamFilesPaths;
    private String fileToPlayPath;
    private String fileToAppendPath;
    private File streamFile;
    private FileInputStream fileInputStream;
    private AudioInputStream stream;
    private AudioFormat format;
    private static int fileNumber;
    private DataLine.Info info;
    private Clip clip;

    public StreamPlayer() {
        fileNumber = 0;
        streamFilesPaths = new LinkedBlockingQueue<>();
        createFirstFile();
    }
    private void createFirstFile(){
       createNewStreamFile("songStream0");
    }

    @Override
    public void run() {
        try {
            fileToPlayPath = streamFilesPaths.poll();
            while(fileToPlayPath != null) {
                fileInputStream = new FileInputStream(fileToPlayPath);
                while (fileInputStream.available() < 100) {
                    fileInputStream = new FileInputStream(fileToPlayPath);
                }
                Player playMP3 = new Player(fileInputStream);
                playMP3.play();
                while(!playMP3.isComplete()){};
                fileToPlayPath = streamFilesPaths.poll();
            }
        } catch (Exception e) {
            log.info("Player MP3 error");
            e.printStackTrace();
        }
    }
    public void handleNewSong(){
        String newName = "songStream" + fileNumber;
        fileNumber++;
        createNewStreamFile(newName);
    }

    public void handleMusicStream(byte[] data) {
        try (FileOutputStream output = new FileOutputStream(fileToAppendPath, true)) {
            output.write(data);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private void createNewStreamFile(String streamFilePath) {
        streamFilesPaths.add(streamFilePath);
        File newFile = new File(streamFilePath);
        try{
            newFile.createNewFile();
        } catch (IOException e){
            log.info("Error during new file creation");
        }
        fileToAppendPath = streamFilePath;
    }
}
