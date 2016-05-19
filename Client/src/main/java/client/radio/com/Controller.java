package client.radio.com;

import lombok.Data;
import lombok.extern.slf4j.Slf4j;

import java.io.DataInputStream;
import java.io.IOException;
import java.net.Socket;
import java.net.UnknownHostException;

/**
 * Created by Michał on 2016-05-04.
 */

@Data
@Slf4j
public class Controller {
    private Player player;
    private Receiver receiver;
    private Playlist playlist;
    private Sender sender;
    private Recorder recorder;
    private Socket socket;

    public static void main(String[] args) throws IOException, InterruptedException {
        
        Controller controller = new Controller();
        String hostName = args[0];
        int portNumber = Integer.parseInt(args[1]);
        try {
            controller.setSocket(new Socket(hostName, portNumber));
        } catch (UnknownHostException e) {
            log.error("Unknown host: " + hostName);
            System.exit(1);
        } catch (IOException e) {
            log.error("No I/O");
            System.exit(1);
        }
        DataInputStream in = new DataInputStream(controller.getSocket().getInputStream());


        Player player = new Player();
        Playlist playlist = new Playlist();
        Receiver receiver = new Receiver(controller.getSocket(), playlist, player, in);
        Sender sender = new Sender(controller.getSocket());

        controller.setReceiver(receiver);
        controller.setSender(sender);

        Thread receiverThread = new Thread(receiver);
        Thread senderThread = new Thread(controller.getSender());

        receiverThread.start();
        senderThread.start();
        receiverThread.join();

        log.info("DONE");
    }
}
