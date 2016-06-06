package client.radio.com;

import groovy.json.internal.ArrayUtils;
import lombok.Data;
import lombok.extern.slf4j.Slf4j;

import java.io.DataOutputStream;
import java.io.File;
import java.io.IOException;
import java.net.Socket;
import java.util.Arrays;
import java.util.stream.Stream;

/**
 * Created by Michał on 2016-04-23.
 */

@Data
@Slf4j
public class Sender implements Runnable {
    private Socket socket;
    private DataOutputStream senderStream;

    public Sender(DataOutputStream senderStream) {
        this.senderStream = senderStream;
        if(senderStream == null)
            log.info("null");
    }

    public void sendVote(int songId, boolean cancelVote) {
            Header header = new Header();
            header.createHeaderVote(cancelVote, (long)32);
        try {
            senderStream.write(header.serializeHeader());
            senderStream.write(intToByteArray(songId));
        } catch (IOException e){
            log.info("Error sending vote");
            e.printStackTrace();
        }
    }

    public void sendMessage(File file) {
    }

    public void sendFile(File file) {
    }

    public void run() {
        //test protocol data
//        byte[] content2 = {90, 0, 2, 0, 0, 0, 4, (byte) 254, (byte) 255, (byte) 254, (byte) 255};
//        byte[] content = {1, 2, 3, 4};
//
//        while (true) {
//            try {
//                for (int i = 0; i < content2.length; i++) {
//                    senderStream.writeByte(content2[i]);
//                }
//            } catch (Exception e) {
//                e.printStackTrace();
//            }
//        }
    }
    private byte[] intToByteArray(int value){
        return new byte[] {
                (byte)(value >>> 24),
                (byte)(value >>> 16),
                (byte)(value >>> 8),
                (byte)value};
    }
}
