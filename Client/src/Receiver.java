package client.radio.com;

import java.io.DataInputStream;
import java.io.File;
import java.io.InputStreamReader;
import java.net.Socket;

/**
 * Created by Michał on 2016-04-23.
 */
public class Receiver implements Runnable{

    private Socket socket;
    private Playlist playlist;
    private Player player;
    private File tempSongFile;
    private DataInputStream receiverStream;

    public Receiver(Socket socket, Playlist playlist, Player player, File tempSongFile, DataInputStream receiverStream) {
        this.socket = socket;
        this.playlist = playlist;
        this.player = player;
        //TO DO - new File, DataInputStream from socket stream
    }

    @Override
    public synchronized void run() {

    }

    private void handleStreamingMusic(){};

    private void handleVoiceMessage(){};

    private void handlePlaylist(){};

    private void appendToTempSongFile(){};

    private void cleanTempSongFile(){};




}
