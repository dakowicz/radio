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
    private String fileToPlayPath;
    private String fileToAppendPath;
    private FileInputStream fileInputStream;
    private boolean running = true;
    private Player playMP3;
    private Playlist playlist;
    private Controller controller;

    public StreamPlayer(Playlist playlist) {
        this.playlist = playlist;
    }

    @Override
    public synchronized void run() {
        try {
            while (playlist.getNextSongToPlay() == null) {
                log.info("czekam");
                try {
                    synchronized (Thread.currentThread()) {
                        Thread.currentThread().wait();
                    }
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
            controller.updatePlaylist();
            Song nextSong = playlist.getNextSongToPlay();
            fileToPlayPath = nextSong.getFileName();
            System.out.println(fileToPlayPath);
            while (running && fileToPlayPath != null) {
                nextSong.setPlayed(true);
                fileInputStream = new FileInputStream(fileToPlayPath);
                while (fileInputStream.available() < 100 && running) {
                    fileInputStream = new FileInputStream(fileToPlayPath);
                }
                playMP3 = new Player(fileInputStream);
                playMP3.play();
                while (!playMP3.isComplete() && running) {          //Aktywne oczekiwanie?+ sleep
                }
                if(running) {
                    controller.updatePlaylist();
                    File file = new File(fileToPlayPath);
                    file.delete();
                    nextSong.setPlayed(false);
                    nextSong.setStreamed(false);
                    nextSong.setVotesNumber(0);

                    nextSong = playlist.getNextSongToPlay();
                    if (nextSong != null) {
                        fileToPlayPath = nextSong.getFileName();
                    } else {
                        fileToPlayPath = null;
                    }
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }//Usuwanie pliku jeśli wyjątek
        return;
    }

    public void handleNewSong(int songId) {
        Song song = playlist.getCurrentPlaylist().get(songId);
                //getNextSongToStream();
        song.setStreamed(true);
        song.setFileName("stream" + song.getId());
        createNewStreamFile(song.getFileName());
    }

    public void handleMusicStream(byte[] data, int songId) {
        fileToAppendPath=playlist.getCurrentPlaylist().get(songId).getFileName();
        try (FileOutputStream output = new FileOutputStream(fileToAppendPath, true)) {
            output.write(data);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private void createNewStreamFile(String streamFilePath) {
        File newFile = new File(streamFilePath);
        try {
            newFile.createNewFile();
        } catch (IOException e) {
            log.info("Error during new file creation");
        }
        fileToAppendPath = streamFilePath;
    }

    public void stopPlayerThread() {
        if (playMP3 != null) {
            playMP3.close();
        }
        running = false;
        playlist.deleteRemainingFiles();    //@TODO Deleting last file
//        playlist.getCurrentPlaylist().forEach((k, v) -> {
//            {
//                if (Files.exists(Paths.get(v.getFileName()))) {
//                    try {
//                        Files.delete(Paths.get(v.getFileName()));
//                    } catch (IOException e) {
//                        log.info("Unable to delete a file");
//                        e.printStackTrace();
//                    }
//                }
//            }
//        });
    }
}
