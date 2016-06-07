package client.radio.com;

import javafx.scene.media.MediaPlayer;
import lombok.Data;
import lombok.extern.slf4j.Slf4j;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
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
    private View view;
    private boolean isPlaying =false;
    private boolean newSong=false;

    private boolean running = true;

    /**
     * To prevent from too large packets
     */
    private static long timeToWaitForPacketInSeconds = 10;

    private Thread receiverThread;
    private Thread senderThread;
    private Thread playerThread;

    private void handlePacketsFromReceiver() throws Exception{
        while (running) {
            DataPacket packet = getReceiver().getDataPackets().poll(timeToWaitForPacketInSeconds, TimeUnit.SECONDS);
            if (packet != null) {
                resolveHeaderType(packet);
            } else {
                gentleExit();
                log.info("Time to wait for packet expired!");
            }
        }
    }
    public void gentleExit(){
        receiver.stopReceiverThread();
        streamPlayer.stopPlayerThread();
        try {
            receiverThread.join();
            playerThread.join();
        } catch (InterruptedException e){
            return;
        }
        running = false;
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
            streamPlayer.handleMusicStream(packet.getMessageByte());
        } else if (packet.getHeader().getParameters() == 1) {
            newSong=false;
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

    public void startApplication() {        //start Threads
        playerThread.start();
        receiverThread.start();
        senderThread.start();
    }

    public void vote(int songId, boolean cancelVote) {
        sender.sendVote(songId, cancelVote);
    }

    @Override
    public void run() {
        try {
            //while (!isPlaying);
            handlePacketsFromReceiver();
        } catch (Exception e) {
            e.printStackTrace();
            //controller.closeApp();
        }
    }

    public void startView(){

        view = new View(playlist);
        view.getPlayButton().addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                //notImplementedPrompt();
                if (isPlaying) {
                    isPlaying = false;
                } else {
                    isPlaying = true;

                }
            }

        });
        //JList listOfSongs= new JList(playlist.getSongsSorted().toArray());
        view.setPlaylist(new JList(playlist.getSongsSorted().toArray()));
        view.getExitButton().addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                //notImplementedPrompt();
                gentleExit();
            }

        });

        view.getVoteButton().addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                view.notImplementedPrompt();

            }

        });



    }


    public static void main(String[] args) throws Exception {
        log.info("start");
        Controller controller = new Controller();
        String hostName = args[0];
        int portNumber = Integer.parseInt(args[1]);

        controller.setupSocketAndStreams(hostName, portNumber);
        controller.setupApplication();
        controller.startApplication();
        controller.handlePacketsFromReceiver();

        controller.startView();
        //Thread controllerThread = new Thread(controller);
        //controllerThread.start();
        //controllerThread.join();
    }

}
