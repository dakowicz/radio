package client.radio.com;
import lombok.Data;
import lombok.extern.slf4j.Slf4j;
/**
 * Created by Michał on 2016-06-03.
 */

@Data
@Slf4j
public class DataPacket {
    private Header header;
    private byte[] messageByte;

    public DataPacket(Header header, byte[] messageByte) {
        this.header = header;
        this.messageByte = messageByte;
    }
}
