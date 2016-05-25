package client.radio.com;

import lombok.Data;
import lombok.extern.slf4j.Slf4j;

import javax.sound.sampled.AudioFileFormat;
import javax.sound.sampled.AudioInputStream;
import javax.sound.sampled.TargetDataLine;
import java.io.File;

/**
 * Created by Michał on 2016-04-23.
 */

@Data
@Slf4j
public class Recorder extends Thread {

    private TargetDataLine dataLine;
    private AudioFileFormat.Type targetType;
    private AudioInputStream audioInputStream;
    private File fileOut;
    private Converter converter;
    private Sender sender;


    public void run() {
    }

    public void convertToMp3() {
    }

    private void startRecording() {
    }

    private void stopRecording() {
    }

    private void sendMessage() {
    }
}
