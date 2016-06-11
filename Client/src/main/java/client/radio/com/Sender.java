package client.radio.com;

import groovy.json.internal.ArrayUtils;
import lombok.Data;
import lombok.extern.slf4j.Slf4j;

import java.io.DataOutputStream;
import java.io.File;
import java.io.IOException;
import java.net.Socket;
import java.util.Arrays;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;
import java.util.stream.Stream;

/**
 * Created by Michał on 2016-04-23.
 */

@Data
@Slf4j
public class Sender implements Runnable {
    private Socket socket;
    private DataOutputStream senderStream;
    private BlockingQueue<DataPacket> dataPackets;
    private boolean running;

    public Sender(DataOutputStream senderStream) {
        this.senderStream = senderStream;
        this.dataPackets = new LinkedBlockingQueue<>();
    }

    public boolean addVoteToSend(int songId, boolean isSongGood) {
        Header header = new Header();
        header.createHeaderVote(isSongGood, (long) 32);
        DataPacket votePacket = new DataPacket(header, intToByteArray(songId));
        dataPackets.add(votePacket);
        return true;
    }

    public void sendMessage(File file) {
    }

    public void sendFile(File file,byte[] bytes) {
    }

    public void run() {
        while(running){
            DataPacket packetToSend = dataPackets.poll();
            try {
                if (packetToSend == null) {
                    synchronized (Thread.currentThread()) {
                        Thread.currentThread().wait();
                    }
                }
                senderStream.write(packetToSend.getHeader().serializeHeader());
                senderStream.write(packetToSend.getMessageByte());
            } catch (Exception e){
                e.printStackTrace();
            }
        }
    }

    private byte[] intToByteArray(int value) {
        return new byte[]{
                (byte) (value >>> 24),
                (byte) (value >>> 16),
                (byte) (value >>> 8),
                (byte) value};
    }
}
