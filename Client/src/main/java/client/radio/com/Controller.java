package client.radio.com;

import javafx.scene.media.MediaPlayer;
import lombok.Data;
import lombok.EqualsAndHashCode;
import lombok.extern.slf4j.Slf4j;

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
@EqualsAndHashCode(exclude = "view")
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
    private boolean isPlaying = false;
    private boolean newSong = false;
    private String hostname;
    private int portNumber;

    private boolean running = true;

    /**
     * To prevent from too large packets
     */
    private static long timeToWaitForPacketInSeconds = 1000;

    private Thread receiverThread;
    private Thread senderThread;
    private Thread playerThread;
    private Thread viewThread;

    private void handlePacketsFromReceiver() throws Exception {
        while (running ) {
            DataPacket packet = getReceiver().getDataPackets().poll(timeToWaitForPacketInSeconds, TimeUnit.SECONDS);
            if (packet != null) {
                resolveHeaderType(packet);
            } else {
                gentleExit();
                log.info("Time to wait for packet expired!");
            }
        }
    }

    public void gentleExit() {
        if(!receiverThread.isAlive()){
            running = false;
            return;
        }

        receiver.stopReceiverThread();
        streamPlayer.stopPlayerThread();
        try {
            receiverThread.join();
            playerThread.join();
        } catch (InterruptedException e) {
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
                handlePlaylist(packet);
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

    public void sendVote(int songId, boolean cancelVote) {
        //log.info("Send Vote");
        if (cancelVote) {
            if (playlist.getCurrentPlaylist().get(songId).isVoted()) {
                playlist.getCurrentPlaylist().get(songId).setVoted(false);
                playlist.vote(songId, cancelVote);
                sender.sendVote(songId, cancelVote);
            } else
                log.info("Already unvoted");
        } else if (!playlist.getCurrentPlaylist().get(songId).isVoted()) {
            sender.sendVote(songId, cancelVote);
            playlist.vote(songId, cancelVote);
        } else
            log.info("Already voted");
        view.updatePlaylist();
    }

    private void handleStreamingMusic(DataPacket packet) {
        log.info("MUSIC");
        if (packet.getHeader().getParameters() == 0) {
            log.info("MP3 DATA");
            streamPlayer.handleMusicStream(packet.getMessageByte());
        } else if (packet.getHeader().getParameters() == 2) {
            log.info("NEW SONG");
            streamPlayer.handleNewSong();
            synchronized (playerThread) {
                playerThread.notify();
            }
            streamPlayer.handleMusicStream(packet.getMessageByte());
        } else if (packet.getHeader().getParameters() == 1) {
            newSong = false;
            log.info("END OF SONG");
        }
    }


    private void handleVoiceMessage() {
        log.info("VOICE MESSAGE");
    }


    private void handlePlaylist(DataPacket packet) {
        log.info("VOTING");
        //log.info(new String(data));
        if (packet.getHeader().getParameters() == 0) {
            log.info("NEW PLAYLIST");
            try {
                playlist.handleNewPlaylist(packet.getMessageByte());
                view.updatePlaylist();
        }catch(IOException e){
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
        setupSocketAndStreams(hostname, portNumber);
        playlist = new Playlist();

        View view1 = new View(this);
        view = view1;
        viewThread = new Thread(view);

        setupThreads();
    }

    public void setupThreads(){
        setStreamPlayer(new StreamPlayer(playlist));
        setReceiver(new Receiver(dataInputStream));
        setSender(new Sender(dataOutputStream));

        setPlayerThread(new Thread(getStreamPlayer()));
        setReceiverThread(new Thread(getReceiver()));
        setSenderThread(new Thread(getSender()));
    }

    public void startApplication() {        //start Threads
        viewThread.start();
    }


    @Override
    public void run() {
        startView();
        try {
            //while (!isPlaying);
            handlePacketsFromReceiver();
        } catch (Exception e2) {
            e2.printStackTrace();
            //controller.closeApp();
        }
    }

    public void startView() {

        //view = new View(playlist);
        view.getPlayButton().addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                //notImplementedPrompt();
                if (isPlaying) {
                    playlist.deleteRemainingFiles();
                    isPlaying = false;
                    streamPlayer.stopPlayerThread();
                    receiver.stopReceiverThread();
                    try {
                        receiverThread.join();
                        playerThread.join();
                        senderThread.join();
                    } catch (InterruptedException e2) {
                        log.info("Threads haven't finished!");
                        return;
                    }
                    try {
                        socket.close();
                    } catch (IOException e1) {
                        e1.printStackTrace();
                    }
                    setupThreads();
                    setupSocketAndStreams(hostname, portNumber);
                } else {
                    isPlaying = true;
                    //setupApplication();
                    senderThread.start();
                    receiverThread.start();
                    playerThread.start();

                }
            }
        });
        //JList listOfSongs= new JList(playlist.getSongsSorted().toArray());
        //view.setPlaylist(new JList(playlist.getSongsSorted().toArray()));
        view.getExitButton().addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                //notImplementedPrompt();
                gentleExit();
            }

        });

    }


    public static void main(String[] args) throws Exception {
        log.info("start");

        Controller controller = new Controller();
        controller.setHostname(args[0]);      //@TODO Just for tasting!
        controller.setPortNumber(Integer.parseInt(args[1]));
        controller.setupSocketAndStreams(controller.getHostname(), controller.getPortNumber());

        controller.setupApplication();
        controller.startApplication();

        //controller.startView();
        Thread controllerThread = new Thread(controller);
        controllerThread.start();
        controllerThread.join();
    }
}
