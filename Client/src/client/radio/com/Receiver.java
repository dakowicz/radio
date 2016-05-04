package client.radio.com;

import java.io.*;
import java.net.Socket;

/**
 * Created by Michał on 2016-04-23.
 */
public class Receiver implements Runnable {

    private Socket socket;
    private Playlist playlist;
    private Player player;
    private File tempSongFile;
    private DataInputStream receiverStream;
    private byte[] messageByte = new byte[4096];

    public Receiver(Socket socket, Playlist playlist, Player player, DataInputStream receiverStream) {
        this.socket = socket;
        this.playlist = playlist;
        this.player = player;
        this.receiverStream = receiverStream;
    }

    @Override
    public synchronized void run() {
        int bytesRead;
        String message = "";
        try {
            while (true) {
                byte[] header = new byte[8];
                header[0] = messageByte[0];
                switch (header[0]) {
                    case 0:
                        break;
                    //TO DO: handling received stream from server and
                    //pass control to adequate handling methods
                }
            }

        } catch (Exception e) {
            e.printStackTrace();
        }
        System.out.println("receiver thread done");
    }

    private void handleStreamingMusic() {
        System.out.println("MUSIC");
    }


    private void handleVoiceMessage() {
        System.out.println("VOICE MESSAGE");
    }


    private void handlePlaylist() {
        System.out.println("NEW PLAYLIST");
    }


    private void appendToTempSongFile() {
    }


    private void cleanTempSongFile() {
    }


}
