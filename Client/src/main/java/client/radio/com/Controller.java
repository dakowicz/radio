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
    private View view;
    private boolean isPlaying = false;
    private boolean newSong = false;
    private String hostname;
    private int portNumber;

    private boolean running = true;

    /**
     * To prevent from too large packets
     */
    private static long timeToWaitForPacketInSeconds = 15;

    private Thread receiverThread;
    private Thread senderThread;
    private Thread playerThread;
    private Thread viewThread;
    private Thread controllerThread;

    private void handlePacketsFromReceiver() throws Exception {
        while (running) {
            DataPacket packet = getReceiver().getDataPackets().poll(timeToWaitForPacketInSeconds, TimeUnit.SECONDS);
            if (packet != null) {
                resolveHeaderType(packet);
            } else {
                gentleExit();
                log.info("Time to wait for packet expired!");
                running = false;
            }
        }
    }

    public void gentleExit() {
        receiver.stopReceiverThread();
        streamPlayer.stopPlayerThread();
        sender.stopSenderThread();
        controllerThread.interrupt();
        try {
            receiverThread.join();
            playerThread.join();
            controllerThread.join();
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


    public void sendVote(int songId, boolean isGoodSong) {
        //log.info("Send Vote");
        if (isGoodSong) {
            if (!playlist.getCurrentPlaylist().get(songId).isVoted()) {
                //playlist.getCurrentPlaylist().get(songId).setVoted(isGoodSong);
                playlist.vote(songId, isGoodSong);
                if (sender.sendVote(songId, isGoodSong)) {
                    synchronized (senderThread) {
                        senderThread.notify();
                    }
                }
            } else {
                log.info("Already unvoted");
            }
        } else if (playlist.getCurrentPlaylist().get(songId).isVoted()) {
            if (sender.sendVote(songId, isGoodSong)) {
                synchronized (senderThread) {
                    senderThread.notify();
                }
            }
            playlist.vote(songId, isGoodSong);
        } else
            log.info("Already voted");
        view.updatePlaylist();
    }

    private void handleStreamingMusic(DataPacket packet) {
        log.info("MUSIC");

        byte[] songIdb = new byte[4];
        byte[] songData = new byte[packet.getMessageByte().length - 4];
        for (int i = 0; i < 4; i++)
            songIdb[i] = packet.getMessageByte()[i];
        for (int i = 0; i < packet.getMessageByte().length - 4; i++)
            songData[i] = packet.getMessageByte()[i + 4];
        int songId;
        songId = songIdb[0] << 24;
        songId += songIdb[1] << 16;
        songId += songIdb[2] << 8;
        songId += songIdb[3];
        log.info("SongId " + String.valueOf(songId));


        if (packet.getHeader().getParameters() == 0) {
            log.info("MP3 DATA");
            if(playlist.getCurrentPlaylist().get(songId).getFileName()==null)
                streamPlayer.handleNewSong(songId);
            synchronized (playerThread) {
                playerThread.notify();
            }
            //streamPlayer.handleMusicStream(packet.getMessageByte());
            streamPlayer.handleMusicStream(songData, songId);
        } else if (packet.getHeader().getParameters() == 2) {
            log.info("NEW SONG");
            //streamPlayer.handleNewSong(songId);
            synchronized (playerThread) {
                playerThread.notify();
            }
            //streamPlayer.handleMusicStream(packet.getMessageByte());
            streamPlayer.handleMusicStream(songData, songId);
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
                log.info(String.valueOf(view.getPlaylist().getModel().getSize()));
                if(view.getPlaylist().getModel().getSize()==0)
                    updatePlaylist();
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

        setView(new View(this));
        viewThread = new Thread(getView());

        setupThreads();
    }

    public void updatePlaylist() {
        log.info("updatePlaylist");
        view.updatePlaylist();
    }

    public void setupThreads() {
        setStreamPlayer(new StreamPlayer(playlist));
        setReceiver(new Receiver(dataInputStream));
        setSender(new Sender(dataOutputStream));

        streamPlayer.setController(this);
        sender.setController(this);
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
            //e2.printStackTrace();
            log.info("controller thread done");
            return;
            //controller.closeApp();
        }
        log.info("controller thread done");
    }

    public void startView() {

        //view = new View(playlist);
     /*   view.getPlayButton().addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                //notImplementedPrompt();
                if (isPlaying) {

                } else {

                }
            }
        });*/
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
        controller.setHostname(args[0]);
        controller.setPortNumber(Integer.parseInt(args[1]));
        //controller.setupSocketAndStreams(controller.getHostname(), controller.getPortNumber());


        controller.setupApplication();
        controller.startApplication();

        //controller.startView();
    }
}
