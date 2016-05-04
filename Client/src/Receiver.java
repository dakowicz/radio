import java.util.Arrays;

/**
 * Created by Kamil on 2016-05-04.
 */
public class Receiver {
    public void convert(byte [] h_data) throws Exception {
        Header header= new Header(Arrays.copyOf(h_data,7));
        switch(header.type){
            case Header.connect:
                if(header.parameters==1)
                    connect(Arrays.copyOfRange(h_data,7,header.length+7));
                if(header.parameters==2)
                    disconnect(Arrays.copyOfRange(h_data,7,header.length+7));
                break;
            case Header.stream:
                if(header.parameters==0)
                    appendToTempFile(Arrays.copyOfRange(h_data,7,header.length+7));
                if(header.parameters==2)
                    startNewSong(Arrays.copyOfRange(h_data, 7, header.length + 7));
                if(header.parameters==1)
                    endCurrentSong(Arrays.copyOfRange(h_data, 7, header.length + 7));
                break;
            case Header.file:
                if(header.parameters==0)
                    handleList(Arrays.copyOfRange(h_data, 7, header.length + 7));
                if(header.parameters==1)
                    ackVote(Arrays.copyOfRange(h_data, 7, header.length + 7));
                break;
        }

    }
    public void connect(byte [] data){
        System.out.println("conect");
        System.out.println(data);
    }

    public void disconnect(byte [] data){

    }

    public void appendToTempFile(byte [] data){

    }

    public void  startNewSong(byte [] data){

    }

    public void  endCurrentSong(byte [] data){

    }

    public void  handleList(byte [] data){

    }

    public void  ackVote(byte [] data){

    }
}
