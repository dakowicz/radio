package client.radio.com;

import java.io.DataOutputStream;
import java.io.File;
import java.io.OutputStream;
import java.net.Socket;

/**
 * Created by Michał on 2016-04-23.
 */
public class Sender implements Runnable {
    Socket socket;
    DataOutputStream senderStream;

    //test protocol data
    byte[] content2 = {(byte) 2, (byte) 0, (byte) 2, (byte) 0, (byte) 0, (byte) 0, (byte) 4, (byte) 254, (byte) 255, (byte) 254, (byte) 255};
    byte[] content = {1, 2, 3, 4};

    public Sender(Socket socket) {
        this.socket = socket;
    }

    public void sendVote(Song song, boolean isGood) {
    }

    public void sendMessage(File file) {
    }

    public void sendFile(File file) {
    }

    @Override
    public void run() {
        while (true) {
            try {
                senderStream = new DataOutputStream(socket.getOutputStream());
                for (int i = 0; i < content.length; i++)
                    senderStream.writeByte(content[i]);
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }
}
