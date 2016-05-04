package client.radio.com;

import java.io.DataOutputStream;
import java.io.File;
import java.io.OutputStream;
import java.net.Socket;

/**
 * Created by Michał on 2016-04-23.
 */
public class Sender {
    Socket socket;
    DataOutputStream senderStream;



    public Sender(Socket socket) {
        this.socket = socket;
    }
    public void sendVote(Song song, boolean isGood){}
    public void sendMessage(File file){}
    public void sendFile(File file){}

}
