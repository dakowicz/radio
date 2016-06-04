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

    private boolean isPlayerRunning = false;
    private DataInputStream receiverStream;
    private BlockingQueue<DataPacket> dataPackets;

    public Receiver(DataInputStream receiverStream) {
        this.receiverStream = receiverStream;
        this.dataPackets = new LinkedBlockingQueue<>();
    }

    public synchronized void run() {
        byte[] data;
        try {
            while (true) {
                byte[] head = new byte[7];
                for (int i = 0; i < 7; i++) {
                    while(receiverStream.available() <= 0){}
                    head[i] = receiverStream.readByte();
                    log.info(String.valueOf(head[i]));
                }
                Header header = new Header(head);
                System.out.println((int)header.getLength());
                data = new byte[(int)header.getLength()+1];
                for (int i = 0; i < (int)header.getLength()+1; i++) {
                    while(receiverStream.available() <= 0){}
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
            log.info("Header error");
            e.printStackTrace();
        }
        log.info("receiver thread done");
    }
}
