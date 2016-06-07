package client.radio.com;


import javazoom.jl.player.Player;
import lombok.Data;
import lombok.extern.slf4j.Slf4j;

import javax.sound.sampled.*;
import java.io.*;
import java.nio.file.Files;
import java.nio.file.Paths;
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
    private boolean running = true;
    private Player playMP3;

    public StreamPlayer() {
        fileNumber = 0;
        streamFilesPaths = new LinkedBlockingQueue<>();
        createFirstFile();
    }

    private void createFirstFile() {
        createNewStreamFile("songStream0");
    }

    @Override
    public synchronized void run() {
        try {
            fileToPlayPath = streamFilesPaths.poll();
            while (running && fileToPlayPath != null) {
                fileInputStream = new FileInputStream(fileToPlayPath);
                while (fileInputStream.available() < 100 && running) {
                    fileInputStream = new FileInputStream(fileToPlayPath);
                }
                playMP3 = new Player(fileInputStream);
                playMP3.play();
                while (!playMP3.isComplete() && running) {          //Aktywne oczekiwanie?
                }
                File file= new File(fileToPlayPath);
                file.delete();
                fileToPlayPath = streamFilesPaths.poll();
            }
        } catch (Exception e){
            e.printStackTrace();
        }//Usuwanie pliku jeśli wyjątek
    }

    public void handleNewSong() {
        String newName = "songStream" + fileNumber;
        if(fileNumber > 0) {
            createNewStreamFile(newName);
        }
        fileNumber++;

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
        try {
            newFile.createNewFile();
        } catch (IOException e) {
            log.info("Error during new file creation");
        }
        fileToAppendPath = streamFilePath;
    }
    public void stopPlayerThread(){
        playMP3.close();
        File file= new File("songStream0");
        file.delete();
        running = false;
    }
}
