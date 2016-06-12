package client.radio.com;


import lombok.Data;
import lombok.extern.slf4j.Slf4j;

import java.io.ByteArrayOutputStream;
import java.io.DataOutputStream;
import java.io.File;

import java.net.Socket;
import java.nio.file.Files;

import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;


/**
 * Created by Michał on 2016-04-23.
 */

@Data
@Slf4j
public class Sender implements Runnable {
    private Socket socket;
    private DataOutputStream senderStream;
    private BlockingQueue<DataPacket> dataPackets;
    private boolean running = true;
    private Controller controller;

    public Sender(DataOutputStream senderStream) {
        this.senderStream = senderStream;
        this.dataPackets = new LinkedBlockingQueue<>();
    }

    public boolean sendVote(int songId, boolean isSongGood) {
        Header header = new Header();
        header.createHeaderVote(isSongGood, (long) 32);
        DataPacket votePacket = new DataPacket(header, intToByteArray(songId));
        dataPackets.add(votePacket);
        return true;
    }

    public void sendMessage(File file) {
    }

    public boolean sendFile(File file, byte[] songInfoByteArray){
        try {
            byte[] fileByteArray = Files.readAllBytes(file.toPath());
            return addFileToSend(fileByteArray, songInfoByteArray);
        }catch (Exception e){
            return false;
        }
    }

    private boolean addFileToSend(byte[] fileByteArray, byte[] songInfoByteArray) {
        Header header = new Header();

        header.createHeaderFile(false, (byte) songInfoByteArray.length, fileByteArray.length);

        ByteArrayOutputStream outputStream = new ByteArrayOutputStream();
        try {
            outputStream.write(songInfoByteArray);
            outputStream.write(fileByteArray);
        } catch (Exception e) {
            return false;
        }

        byte byteArrayToSend[] = outputStream.toByteArray();
        dataPackets.add(new DataPacket(header, byteArrayToSend));
        return true;
    }

    public void run() {
        log.info("sender thread start");
        while (running) {
            try {
                DataPacket packetToSend = dataPackets.take();
                log.info("packet taken");
                if (packetToSend == null) {
                    log.info("waiting");
                    synchronized (Thread.currentThread()) {
                        Thread.currentThread().wait();
                        packetToSend = dataPackets.take();
                    }
                }
                log.info("send!");
                senderStream.write(packetToSend.getHeader().serializeHeader());
                senderStream.write(packetToSend.getMessageByte());
            } catch (InterruptedException e) {
                log.info("sender thread done");
                return;
            } catch (Exception e){
                e.printStackTrace();
            }
        }
    }

    public void stopSenderThread() {
        running = false;
        synchronized (controller.getSenderThread()) {
            controller.getSenderThread().interrupt();
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
