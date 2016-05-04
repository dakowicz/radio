package client.radio.com;

import javax.sound.sampled.AudioFileFormat;
import javax.sound.sampled.AudioInputStream;
import javax.sound.sampled.TargetDataLine;
import java.io.File;

/**
 * Created by Michał on 2016-04-23.
 */
public class Recorder extends Thread{

    private TargetDataLine dataLine;
    private AudioFileFormat.Type targetType;
    private AudioInputStream audioInputStream;
    private File fileOut;
    private Converter converter;
    private Sender sender;




    public void run(){}

    public void convertToMp3(){};

    private void startRecording(){};

    private void stopRecording(){};

    private void sendMessage(){}

    public Converter getConverter() {
        return converter;
    }

    public void setConverter(Converter converter) {
        this.converter = converter;
    }

    public void setDataLine(TargetDataLine dataLine) {
        this.dataLine = dataLine;
    }

    public void setTargetType(AudioFileFormat.Type targetType) {
        this.targetType = targetType;
    }

    public void setAudioInputStream(AudioInputStream audioInputStream) {
        this.audioInputStream = audioInputStream;
    }

    public void setFileOut(File fileOut) {
        this.fileOut = fileOut;
    }


    public TargetDataLine getDataLine() {
        return dataLine;
    }

    public AudioFileFormat.Type getTargetType() {
        return targetType;
    }

    public AudioInputStream getAudioInputStream() {
        return audioInputStream;
    }

    public File getFileOut() {
        return fileOut;
    }

    public Sender getSender() {
        return sender;
    }

    public void setSender(Sender sender) {
        this.sender = sender;
    }

}
