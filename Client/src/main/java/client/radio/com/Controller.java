package client.radio.com;

import javafx.scene.media.MediaPlayer;
import lombok.Data;
import lombok.extern.slf4j.Slf4j;

import java.io.DataInputStream;
import java.io.IOException;
import java.net.Socket;
import java.net.UnknownHostException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

/**
 * Created by Michał on 2016-05-04.
 */

@Data
@Slf4j
public class Controller {
    private Receiver receiver;
    private Playlist playlist;
    private Sender sender;
    private Recorder recorder;
    private Socket socket;
    private App app;
    private MediaPlayer mediaPlayer;

    private ExecutorService executor = Executors.newFixedThreadPool(5);
    private Thread receiverThread;
    private Thread senderThread;
    private Thread playerThread;
    private Thread appThread;

    public void setSocket(Socket socket) {
        this.socket = socket;
    }
    private void startAppThread() {
        try {
            this.getExecutor().execute(appThread);
        } catch (IllegalStateException e) {
            e.printStackTrace();
        }
    }
    private void startReceiverThread() {
        try {
            this.getExecutor().execute(receiverThread);
        } catch (IllegalStateException e) {
            e.printStackTrace();
        }
    }

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

        App app = new App();
        controller.setApp(app);
        controller.setAppThread(new Thread(controller.getApp()));
        controller.startAppThread();

        Playlist playlist = new Playlist();

        Receiver receiver = new Receiver(controller.getSocket(), playlist, app, controller, in);
        controller.setReceiver(receiver);
        controller.setReceiverThread(new Thread(controller.getReceiver()));
        controller.startReceiverThread();
    }
}
