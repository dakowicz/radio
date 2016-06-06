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
    private long length;

    public Header(byte head[]) throws Exception {
        if (head[0] != ID_PROT || head[1] > 3) {
            throw new Exception("Wrong protocol - was: " + head[0]);
        }
        type = head[1];
        parameters = head[2];
        if (head[6] < 0)
            head[5]++;
        if (head[5] < 0)
            head[4]++;
        if (head[4] < 0)
            head[3]++;
        length = head[3] << 24;
        length += head[4] << 16;
        length += head[5] << 8;
        length += head[6];
    }
    public Header(){};

    public void createHeader(byte t, byte param, long lng) {
        type = t;
        parameters = param;
        length = lng;

    }

    public void createHeaderConnect(boolean start, boolean end, long lng) {
        type = CONNECT;
        parameters = (byte) (start ? 1 : 0);
        parameters += (byte) (end ? 2 : 0);
        length = lng;
    }


    public void createHeaderVote(boolean cancelVote, long lng) {
        type = VOTES;
        parameters = (byte) (cancelVote ? 1 : 0);
        parameters += 2;    //Since it's the client to server message
        length = lng;
    }

    public void createHeaderFile(boolean priority, byte infoLength, long lng) {
        type = FILE;
        if (infoLength < 0) {
            return;
        }
        parameters = infoLength;
        parameters += (byte) (priority ? -128 : 0);
        length = lng;
    }

    public byte[] serializeHeader() {
        byte[] head = new byte[7];
        head[0] = ID_PROT;
        head[1] = type;
        head[2] = parameters;
        head[3] = (byte) (length >>> 24);
        head[4] = (byte) (length >>> 16);
        head[5] = (byte) (length >>> 8);
        head[6] = (byte) length;
        return head;
    }
}