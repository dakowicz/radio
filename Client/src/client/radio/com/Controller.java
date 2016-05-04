package client.radio.com;

import java.io.*;
import java.net.Socket;
import java.net.UnknownHostException;

/**
 * Created by Michał on 2016-05-04.
 */
public class Controller {
    private Player player;
    private Receiver receiver;
    private Playlist playlist;
    private Sender sender;
    private Recorder recorder;
    private Socket socket;


    public Player getPlayer() {
        return player;
    }

    public void setPlayer(Player player) {
        this.player = player;
    }

    public Receiver getReceiver() {
        return receiver;
    }

    public void setReceiver(Receiver receiver) {
        this.receiver = receiver;
    }

    public Playlist getPlaylist() {
        return playlist;
    }

    public void setPlaylist(Playlist playlist) {
        this.playlist = playlist;
    }

    public Sender getSender() {
        return sender;
    }

    public void setSender(Sender sender) {
        this.sender = sender;
    }

    public Recorder getRecorder() {
        return recorder;
    }

    public void setRecorder(Recorder recorder) {
        this.recorder = recorder;
    }

    public Socket getSocket() {
        return socket;
    }

    public void setSocket(Socket socket) {
        this.socket = socket;
    }


    public static void main(String[] args) throws IOException, InterruptedException {

        Controller controller = new Controller();
        String hostName = args[0];
        int portNumber = Integer.parseInt(args[1]);
        try {
            controller.setSocket(new Socket(hostName, portNumber));
        } catch (UnknownHostException e) {
            System.out.println("Unknown host: " + hostName);
            System.exit(1);
        } catch (IOException e) {
            System.out.println("No I/O");
            System.exit(1);
        }
        DataInputStream in = new DataInputStream(controller.getSocket().getInputStream());


        Player player = new Player();
        Playlist playlist = new Playlist();
        Receiver receiver = new Receiver(controller.getSocket(), playlist, player, in);

        controller.setReceiver(receiver);

        Thread receiverThread = new Thread(receiver);

        receiverThread.start();
        receiverThread.join();

        System.out.println("DONE");
    }


}
