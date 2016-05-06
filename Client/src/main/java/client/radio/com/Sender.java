package client.radio.com;

import lombok.Data;

import java.io.DataOutputStream;
import java.io.File;
import java.net.Socket;

/**
 * Created by Michał on 2016-04-23.
 */

@Data
public class Sender {
    private Socket socket;
    private DataOutputStream senderStream;

    public void sendVote(Song song, boolean isGood) {
    }

    public void sendMessage(File file) {
    }

    public void sendFile(File file) {
    }

}
