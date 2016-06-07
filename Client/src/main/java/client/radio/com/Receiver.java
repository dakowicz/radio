package client.radio.com;

import lombok.Data;
import lombok.extern.slf4j.Slf4j;

import java.io.DataInputStream;
import java.io.EOFException;
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
    private volatile boolean running = true;

    public Receiver(DataInputStream receiverStream) {
        this.receiverStream = receiverStream;
        this.dataPackets = new LinkedBlockingQueue<>();
    }

    public synchronized void run() {
        byte[] data;
        try {
            while (running) {

                byte[] head = new byte[7];
                for (int i = 0; i < 7; i++) {
                    while (receiverStream.available() <= 0 && running) {
                    }
                    if (running) {
                        head[i] = receiverStream.readByte();
                        log.info(String.valueOf(head[i]));
                    }
                }
                if (running) {
                    Header header = new Header(head);
                    data = new byte[(int) header.getLength()];
                    for (int i = 0; i < (int) header.getLength(); i++) {
                        if (running) {
                            while (receiverStream.available() <= 0 && running) {
                            }
                            try {
                                data[i] = receiverStream.readByte();
                            } catch (EOFException e) {
                                log.info("eof");
                                //e.printStackTrace();
                                continue;
                            }
                        }
                    }
                    dataPackets.add(new DataPacket(header, data));
                }
            }
        } catch (InterruptedException e) {
            log.info("Thread interrupted");
            return;
        } catch (
                Exception e
                )

        {
            log.info("Header error");
            e.printStackTrace();
        }

        log.info("receiver thread done");
    }

    public void stopReceiverThread() {
        running = false;
    }
}
