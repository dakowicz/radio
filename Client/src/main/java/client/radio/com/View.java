package client.radio.com;

import javazoom.jl.player.Player;
import lombok.Data;
import lombok.EqualsAndHashCode;
import lombok.extern.slf4j.Slf4j;

import javax.swing.*;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.FocusAdapter;
import java.io.IOException;

/**
 * Created by Kamil on 2016-06-06.
 */

@Data
@Slf4j
@EqualsAndHashCode(exclude="controller")
public class View extends JFrame implements Runnable{
    private Controller controller;
    private Playlist playlistData;
    private JPanel rootPanel;
    public JList<Song> playlist;
    private JLabel radioLabel;
    private JButton voteButton;
    private JButton playButton;
    private JButton exitButton;
    private JButton recordButton;
    private boolean isPlaying = false;


    class MyCellRenderer extends DefaultListCellRenderer
    {
        public Component getListCellRendererComponent(JList<? extends Song> list, Song value, int index, boolean isSelected, boolean cellHasFocus) {
        {
            //super.getListCellRendererComponent(list,value, index, isSelected, cellHasFocus);
            Color bg = new Color(160, 255, 155);
            if(value.isVoted())
                setBackground(bg);
            setOpaque(true); // otherwise, it's transparent
            return this;  // DefaultListCellRenderer derived from JLabel, DefaultListCellRenderer.getListCellRendererComponent returns this as well.
        }
        }
    }

    public View(Controller controller1) {
        super("TINy RADIO");
        controller=controller1;
        playlistData = controller.getPlaylist();
        Song[] songs=new Song[1];
        playlist.setListData(playlistData.getSongsToDisplay().toArray(songs));
        playlist.setCellRenderer(new MyCellRenderer());
        try {
            for (UIManager.LookAndFeelInfo info : UIManager.getInstalledLookAndFeels()) {
                if ("Nimbus".equals(info.getName())) {
                    UIManager.setLookAndFeel(info.getClassName());
                    break;
                }
            }
        } catch (Exception e) {
            // If Nimbus is not available, you can set the GUI to another look and feel.
        }
        //this.setAlwaysOnTop(true);

        ImageIcon stopIcon = new ImageIcon("Client/ref/stop.png");
        ImageIcon playIcon = new ImageIcon("Client/ref/playMy.png");
        ImageIcon recordIcon = new ImageIcon("Client/ref/record.png");
        ImageIcon exitIcon = new ImageIcon("Client/ref/exitsmall.png");

        playButton.setIcon(playIcon);
        playButton.setOpaque(false);
        playButton.setContentAreaFilled(false);
        playButton.setBorderPainted(false);

        recordButton.setIcon(recordIcon);
        recordButton.setOpaque(false);
        recordButton.setContentAreaFilled(false);
        recordButton.setBorderPainted(false);

        exitButton.setIcon(exitIcon);
        exitButton.setOpaque(false);
        exitButton.setContentAreaFilled(false);
        exitButton.setBorderPainted(false);

        MoveMouseListener mml = new MoveMouseListener(rootPanel);
        rootPanel.addMouseListener(mml);
        rootPanel.addMouseMotionListener(mml);
        setUndecorated(true);

        //setShape(new RoundRectangle2D.Double(10, 10, 100, 100, 50, 50));
        //setSize(300, 200);

        setContentPane(rootPanel);
        pack();
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);
        setVisible(true);

        voteButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                if(playlist.getSelectedIndex()==-1)
                    selectSongPrompt();
                else {
                    Song song=playlist.getSelectedValue();
                    if (song.isVoted()) {
                        log.info("Send unvote");
                        controller.sendVote(song.getId(),true);
                    }
                    else
                    if (!song.isVoted()) {
                        log.info("Send vote");
                        controller.sendVote(song.getId(),false);
                    }
                }
            }
        });

        playButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                //notImplementedPrompt();
                if (isPlaying) {
                    playButton.setIcon(playIcon);
                    isPlaying = false;

                    //controller1.getPlaylist().deleteRemainingFiles();
                    isPlaying = false;
                    controller1.getStreamPlayer().stopPlayerThread();
                    controller1.getReceiver().stopReceiverThread();
                    try {
                        controller1.getReceiverThread().join();
                        controller1.getPlayerThread().join();
                        controller1.getSenderThread().join();
                        controller1.getControllerThread().interrupt();
                    } catch (InterruptedException e2) {
                        log.info("Threads haven't finished!");
                        return;
                    }
                    try {
                        controller1.getSocket().close();
                    } catch (IOException e1) {
                        e1.printStackTrace();
                    }
                    log.info("Nowa Playlista");
                    controller1.setPlaylist(new Playlist());
                    log.info(playlist.toString());
                    updatePlaylist();
                    controller1.setupSocketAndStreams(controller1.getHostname(), controller1.getPortNumber());
                    controller1.setupThreads();
                } else {
                    controller1.setControllerThread(new Thread(controller1));
                    controller1.getControllerThread().start();
                    isPlaying = true;
                    //setupApplication();
                    controller1.getSenderThread().start();
                    controller1.getReceiverThread().start();
                    controller1.getPlayerThread().start();
                    //isPlaying = true;
                    playButton.setIcon(stopIcon);
                }
            }
        });
        exitButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                controller1.getPlaylist().deleteRemainingFiles();
                setVisible(false);
                dispose();
            }
        });
        recordButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                premiumVersionPrompt();
            }
        });

    }

    private void selectSongPrompt() {
        JOptionPane.showMessageDialog(View.this, "Please select a song");
    }

    public void notImplementedPrompt() {
        //JOptionPane.showConfirmDialog(View.this, "Not implemented yet");
        JOptionPane.showMessageDialog(View.this, "Not implemented yet");
    }

    private void premiumVersionPrompt() {
        //JOptionPane.showConfirmDialog(View.this, "Not implemented yet");
        JOptionPane.showMessageDialog(View.this, "Upgrade to the premium version for only $0.99/month");
    }
    private void alreadyVotedPrompt() {
        //JOptionPane.showConfirmDialog(View.this, "Not implemented yet");
        JOptionPane.showMessageDialog(View.this, "You've already voted on this song");
    }

    public void updatePlaylist(){
        Song[] songs=new Song[1];
        playlist.setListData(songs);
        playlist.setListData(controller.getPlaylist().getSongsToDisplay().toArray(songs));
        //log.info(playlistData.toString());
    }

    public void run() {

    }
}
