/**
 * Created by Kamil on 2016-05-04.
 */
public class Header {
    static byte connect=0;
    static byte stream=1;
    static byte votes=2;
    static byte file=3;
    static byte id_prot=2;
    byte type; //Here is also the zero-tail
    byte parameters;
    int length;

    public Header(){

    }

    public Header(byte head[]) throws Exception{
        if(head[0]!=id_prot|| head[1]>3)
            throw new Exception("Wrong protocol");
        type=head[1];
        parameters=head[2];
        length=head[3]<<24;
        length+=head[4]<<16;
        length+=head[5]<<8;
        length+=head[6];
    }
    public void createHeader(byte t, byte param, int l){
        type=t;
        parameters=param;
        length=l;

    }

    public void createHeaderConnect(boolean start, boolean end, int l){
        type=connect;
        parameters=(byte)(start?1:0);
        parameters+=(byte)(end?2:0);
        length=l;
    }
    public void createHeaderVote(boolean cancel_vote, int l){
        type=votes;
        parameters=(byte)(cancel_vote?1:0);
        parameters+=2;	//Since it's the client to server message
        length=l;
    }
    public void createHeaderFile(boolean priority, byte info_length, int l){
        type=file;
        if(info_length<0)
            return;
        parameters=info_length;
        parameters+=(byte)(priority?-128:0);
        length=l;
    }

}

