package client.radio.com;

import lombok.Data;
import lombok.extern.slf4j.Slf4j;

import java.io.DataInputStream;
import java.io.File;
import java.net.Socket;

/**
 * Created by Michał on 2016-04-23.
 */

@Slf4j
@Data
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

    public synchronized void run() {
        int bytesRead;
        byte[] data;
        String message = "";
        try {
            while (true) {
                byte[] head = new byte[7];
                for (int i = 0; i < 7; i++) {
                    head[i] = receiverStream.readByte();
                }
                Header header = new Header(head);
                data = new byte[header.getLength()];
                for (int i = 0; i < header.getLength(); i++) {
                    try {
                        data[i] = receiverStream.readByte();
                    } catch (Exception e) {
                        continue;
                    }
                }
                resolveHeaderType(header, data);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        log.info("receiver thread done");
    }

    private void resolveHeaderType(Header header, byte[] data) {
        switch (header.getType()) {
            case Header.CONNECT:
                handleConnectionSignal(header, data);
                break;
            case Header.STREAM:
                handleStreamingMusic(header, data);
                break;
            case Header.VOTES:
                handleVoting(header, data);
                break;
            default:
        }
    }

    private void handleConnectionSignal(Header header, byte[] data) {
        if (header.getParameters() == 1) {
            log.info(new String(data));
            log.info("CONNECT SIGNAL RECEIVED");
        }
            //CONNECT(Arrays.copyOfRange(h_data, 7, header.length + 7));
        else if (header.getParameters() == 2) {
            log.info(new String(data));
            log.info("DISCONNECT SIGNAL RECEIVED");
        }
        // disconnect(Arrays.copyOfRange(h_data, 7, header.length + 7));
    }

    private void handleStreamingMusic(Header header, byte[] data) {
        log.info("MUSIC");
        log.info(new String(data));
        if (header.getParameters() == 0) {
            log.info("MP3 DATA");
        }
            //appendToTempFile(Arrays.copyOfRange(h_data, 7, header.length + 7));
        else if (header.getParameters() == 2) {
            log.info("NEW SONG");
        }
            //startNewSong(Arrays.copyOfRange(h_data, 7, header.length + 7));
        else if (header.getParameters() == 1) {
            log.info("END OF SONG");
        }
        //endCurrentSong(Arrays.copyOfRange(h_data, 7, header.length + 7));
    }


    private void handleVoiceMessage() {
        log.info("VOICE MESSAGE");
    }


    private void handleVoting(Header header, byte[] data) {
        log.info("VOTING");
        log.info(new String(data));
        if (header.getParameters() == 0) {
            log.info("NEW PLAYLIST");
        }
        //handleList(Arrays.copyOfRange(h_data, 7, header.length + 7));
        if (header.getParameters() == 1) {
            log.info("VOTE ACK");
        }
        //ackVote(Arrays.copyOfRange(h_data, 7, header.length + 7));
    }


    private void appendToTempSongFile() {
    }


    private void cleanTempSongFile() {
    }


}
