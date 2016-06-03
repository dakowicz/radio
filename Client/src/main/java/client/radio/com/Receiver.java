package client.radio.com;

import lombok.Data;
import lombok.extern.slf4j.Slf4j;

import java.io.DataInputStream;
import java.io.EOFException;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.net.Socket;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;

/**
 * Created by Michał on 2016-04-23.
 */

@Slf4j
@Data
public class Receiver implements Runnable {

    private Socket socket;
    private Playlist playlist;
    private App app;
    private Controller controller;
    private boolean isPlayerRunning = false;
    private FileOutputStream songStreamFile;
    private DataInputStream receiverStream;
    private BlockingQueue<DataPacket> dataPackets;

    public Receiver(Socket socket, Playlist playlist, App app, Controller controller, DataInputStream receiverStream) {
        this.socket = socket;
        this.playlist = playlist;
        this.app = app;
        this.controller = controller;
        this.receiverStream = receiverStream;
        this.dataPackets = new LinkedBlockingQueue<>();
        try {
            songStreamFile = new FileOutputStream("songStream.mp3");
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
    }

    public synchronized void run() {
        byte[] data;
        try {
            while (true) {
                byte[] head = new byte[7];
                for (int i = 0; i < 7; i++) {
                    head[i] = receiverStream.readByte();
                    log.info(String.valueOf(head[i]));
                }
                Header header = new Header(head);
                data = new byte[(int)header.getLength()];
                for (int i = 0; i < (int)header.getLength(); i++) {
                    try {
                        data[i] = receiverStream.readByte();
                    } catch (EOFException e) {
                        log.info("eof");
                        //e.printStackTrace();
                        continue;
                    }
                }
                dataPackets.add(new DataPacket(header, data));
            }
        } catch (Exception e) {
            log.info("Eof header");
            e.printStackTrace();
        }
        log.info("receiver thread done");
    }
}
