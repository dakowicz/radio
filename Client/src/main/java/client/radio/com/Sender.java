package client.radio.com;

import lombok.Data;
import lombok.extern.slf4j.Slf4j;

import java.io.DataOutputStream;
import java.io.File;
import java.net.Socket;

/**
 * Created by Michał on 2016-04-23.
 */

@Data
@Slf4j
public class Sender implements Runnable {
    private Socket socket;
    private DataOutputStream senderStream;

    public Sender(Socket socket) {
        this.socket = socket;
    }

    public void sendVote(Song song, boolean isGood) {
    }

    public void sendMessage(File file) {
    }

    public void sendFile(File file) {
    }

    public void run() {
        //test protocol data
        byte[] content2 = {90,  0,  2,  0,  0,  0,  4, (byte) 254, (byte) 255, (byte) 254, (byte) 255};
        byte[] content = {1, 2, 3, 4};

        while (true) {
            try {
                senderStream = new DataOutputStream(socket.getOutputStream());
                for (int i = 0; i < content2.length; i++) {
                    senderStream.writeByte(content2[i]);
                }
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }
}
