package client.radio.com;

import lombok.Data;
import lombok.extern.slf4j.Slf4j;

import javax.swing.*;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

/**
 * Created by Kamil on 2016-06-06.
 */

@Data
@Slf4j
public class View extends JFrame implements Runnable{
    private Playlist playlistData;
    private JPanel rootPanel;
    private JList<Object> playlist;
    private JLabel radioLabel;
    private JButton voteButton;
    private JButton playButton;
    private JButton exitButton;
    private JButton recordButton;
    private boolean isplaying = false;


    public View(Playlist playlistInData) {
        super("TINy RADIO");
        playlistData = playlistInData;

        playlist.setListData(playlistData.getSongsToDisplay().toArray());
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
            }
        });

        playButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                //notImplementedPrompt();
                if (isplaying) {
                    playButton.setIcon(playIcon);
                    isplaying = false;
                } else {
                    isplaying = true;
                    playButton.setIcon(stopIcon);
                }
            }
        });
        exitButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
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

    public void run() {

    }
}
