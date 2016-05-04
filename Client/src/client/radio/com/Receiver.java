package client.radio.com;

import java.io.*;
import java.net.Socket;
import java.util.Arrays;

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
                byte[] head = new byte[7];
                for (int i = 0; i < 7; i++) {
                    head[i] = receiverStream.readByte();
                }
                Header header = new Header(head);
                resolveHeaderType(header);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        System.out.println("receiver thread done");
    }

    private void resolveHeaderType(Header header) {
        switch (header.type) {
            case Header.connect:
                handleConnectionSignal(header);
                break;
            case Header.stream:
                handleStreamingMusic(header);
                break;
            case Header.votes:
                handleVoting(header);
                break;
        }
    }

    private void handleConnectionSignal(Header header) {
        if (header.parameters == 1)
            System.out.println("CONNECT SIGNAL RECEIVED");
            //connect(Arrays.copyOfRange(h_data, 7, header.length + 7));
        else if (header.parameters == 2)
            System.out.println("DISCONNECT SIGNAL RECEIVED");
        // disconnect(Arrays.copyOfRange(h_data, 7, header.length + 7));
    }

    private void handleStreamingMusic(Header header) {
        System.out.println("MUSIC");
        if (header.parameters == 0)
            System.out.println("MP3 DATA");
            //appendToTempFile(Arrays.copyOfRange(h_data, 7, header.length + 7));
        else if (header.parameters == 2)
            System.out.println("NEW SONG");
            //startNewSong(Arrays.copyOfRange(h_data, 7, header.length + 7));
        else if (header.parameters == 1)
            System.out.println("END OF SONG");
        //endCurrentSong(Arrays.copyOfRange(h_data, 7, header.length + 7));
    }


    private void handleVoiceMessage() {
        System.out.println("VOICE MESSAGE");
    }


    private void handleVoting(Header header) {
        System.out.println("VOTING");
        if (header.parameters == 0)
            System.out.println("NEW PLAYLIST");
        //handleList(Arrays.copyOfRange(h_data, 7, header.length + 7));
        if (header.parameters == 1)
            System.out.println("VOTE ACK");
        //ackVote(Arrays.copyOfRange(h_data, 7, header.length + 7));
    }


    private void appendToTempSongFile() {
    }


    private void cleanTempSongFile() {
    }


}
