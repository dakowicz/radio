package client.radio.com;

import javafx.scene.media.MediaPlayer;
import lombok.Data;
import lombok.extern.slf4j.Slf4j;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.Socket;
import java.net.UnknownHostException;
import java.util.concurrent.TimeUnit;

/**
 * Created by Michał on 2016-05-04.
 */

@Data
@Slf4j
public class Controller implements Runnable {
    private Receiver receiver;
    private Playlist playlist;
    private Sender sender;
    private StreamPlayer streamPlayer;
    private Recorder recorder;
    private Socket socket;
    private DataInputStream dataInputStream;
    private DataOutputStream dataOutputStream;
    private MediaPlayer mediaPlayer;

    /**
     * To prevent from too large packets
     */
    private static long timeToWaitForPacketInSeconds = 35;

    private Thread receiverThread;
    private Thread senderThread;
    private Thread playerThread;

    private void handlePacketsFromReceiver() throws Exception {
        while (true) {
            DataPacket packet = getReceiver().getDataPackets().poll(timeToWaitForPacketInSeconds, TimeUnit.SECONDS);
            if (packet != null) {
                resolveHeaderType(packet);
            } else {
                throw new Exception("Packet too large!");
            }
        }
    }

    private void resolveHeaderType(DataPacket packet) {
        switch (packet.getHeader().getType()) {
            case Header.CONNECT:
                log.info("connect");
                //handleConnectionSignal(packet);
                break;
            case Header.STREAM:
                log.info("stream");
                handleStreamingMusic(packet);
                break;
            case Header.VOTES:
                handleVoting(packet);
                break;
        }
    }

    private void handleConnectionSignal(Header header, byte[] data) {
        if (header.getParameters() == 1) {
            log.info(new String(data));
            log.info("CONNECT SIGNAL RECEIVED");
        }
        //CONNECT(Arrays.copyOfRange(h_data, 7, header.length + 7));
        else if (header.getParameters() == 2) {
            log.info(new String(data));
            log.info("DISCONNECT SIGNAL RECEIVED");
        }
        // disconnect(Arrays.copyOfRange(h_data, 7, header.length + 7));
    }

    private void handleStreamingMusic(DataPacket packet) {
        log.info("MUSIC");
        if (packet.getHeader().getParameters() == 0) {
            log.info("MP3 DATA");
            streamPlayer.handleMusicStream(packet.getMessageByte());
        } else if (packet.getHeader().getParameters() == 2) {
            log.info("NEW SONG");
            streamPlayer.handleNewSong();
        } else if (packet.getHeader().getParameters() == 1) {
            log.info("END OF SONG");
        }
    }


    private void handleVoiceMessage() {
        log.info("VOICE MESSAGE");
    }


    private void handleVoting(DataPacket packet) {
        log.info("VOTING");
        //log.info(new String(data));
        if (packet.getHeader().getParameters() == 0) {
            log.info("NEW PLAYLIST");
            try {
                playlist.handleNewPlaylist(packet.getMessageByte());
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
        //handleList(Arrays.copyOfRange(h_data, 7, header.length + 7));
        //ackVote(Arrays.copyOfRange(h_data, 7, header.length + 7));
    }

    public void setupSocketAndStreams(String hostName, int portNumber) {
        try {
            setSocket(new Socket(hostName, portNumber));
            dataInputStream = new DataInputStream(getSocket().getInputStream());
            dataOutputStream = new DataOutputStream(getSocket().getOutputStream());
        } catch (UnknownHostException e) {
            log.error("Unknown host: " + hostName);
            System.exit(1);
        } catch (IOException e) {
            log.error("No I/O");
            System.exit(1);
        }

    }

    public void setupApplication() {
        setStreamPlayer(new StreamPlayer());
        setPlayerThread(new Thread(getStreamPlayer()));

        playlist = new Playlist(streamPlayer);

        setReceiver(new Receiver(dataInputStream));
        setReceiverThread(new Thread(getReceiver()));

        setSender(new Sender(dataOutputStream));
        setSenderThread(new Thread(getSender()));

    }

    public void startApplication() {
        playerThread.start();
        receiverThread.start();
        senderThread.start();
    }

    @Override
    public void run() {
        try {
            handlePacketsFromReceiver();
        } catch (Exception e) {
            e.printStackTrace();
            //controller.closeApp();
        }
    }

    public static void main(String[] args) throws IOException, InterruptedException {
        log.info("start");
        Controller controller = new Controller();
        String hostName = args[0];
        int portNumber = Integer.parseInt(args[1]);

        controller.setupSocketAndStreams(hostName, portNumber);
        controller.setupApplication();
        controller.startApplication();

        Thread controllerThread = new Thread(controller);
        controllerThread.start();

    }

}
