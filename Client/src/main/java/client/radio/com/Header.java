package client.radio.com;

import lombok.Data;

/**
 * Created by Kamil on 2016-05-04.
 */

@Data
public class Header {
    static final byte CONNECT = 0;
    static final byte STREAM = 1;
    static final byte VOTES = 2;
    static final byte FILE = 3;
    static final byte ID_PROT = 90;
    private byte type; //Here is also the zero-tail
    private byte parameters;
    private int length;

    public Header(byte head[]) throws Exception {
        if (head[0] != ID_PROT || head[1] > 3) {
            throw new Exception("Wrong protocol");
        }
        type = head[1];
        parameters = head[2];
        length = head[3] << 24;
        length += head[4] << 16;
        length += head[5] << 8;
        length += head[6];
    }

    public void createHeader(byte t, byte param, int lng) {
        type = t;
        parameters = param;
        length = lng;

    }

    public void createHeaderConnect(boolean start, boolean end, int lng) {
        type = CONNECT;
        parameters = (byte) (start ? 1 : 0);
        parameters += (byte) (end ? 2 : 0);
        length = lng;
    }


    public void createHeaderVote(boolean cancelVote, int lng) {
        type = VOTES;
        parameters = (byte) (cancelVote ? 1 : 0);
        parameters += 2;    //Since it's the client to server message
        length = lng;
    }

    public void createHeaderFile(boolean priority, byte infoLength, int lng) {
        type = FILE;
        if (infoLength < 0) {
            return;
        }
        parameters = infoLength;
        parameters += (byte) (priority ? -128 : 0);
        length = lng;
    }

}
