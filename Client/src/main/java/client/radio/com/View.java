package client.radio.com;

import lombok.Data;

/**
 * Created by Michał on 2016-04-23.
 */

@Data
public class View {
    private Player player;
    private Receiver receiver;
    private Playlist playlist;
    private Sender sender;
    private Recorder recorder;
    private Controller controller;
}
