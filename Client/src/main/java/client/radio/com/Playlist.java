package client.radio.com;

import com.sun.xml.internal.messaging.saaj.util.CharReader;
import lombok.Data;
import lombok.extern.slf4j.Slf4j;

import java.io.*;
import java.util.*;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.ConcurrentMap;

import org.apache.commons.csv.*;

/**
 * Created by Michał on 2016-04-23.
 */

@Data
@Slf4j
public class Playlist {

    public static char separator = '\n';
    private ConcurrentMap<Integer, Song> CurrentPlaylist;
    private CSVParser parser;


    public Playlist() {
        CurrentPlaylist = new ConcurrentHashMap<Integer, Song>();
    }

    public void checkVoted(int songId) {
        try {
            CurrentPlaylist.get(songId).setVoted(true);
        } catch (NullPointerException e) {
            log.info("No such a song");
        }
    }

    public void checkUnvoted(int songId) {
        try {
            CurrentPlaylist.get(songId).setVoted(false);
        } catch (NullPointerException e) {
            log.info("No such a song");
        }
    }

    private void createPlaylist(List<CSVRecord> list) {
        log.info(list.get(0).toString());
        Iterator<CSVRecord> iterator = list.iterator();
        while (iterator.hasNext()) {
            CSVRecord record = iterator.next();
            Song song = new Song(record.get(1), record.get(2), Integer.valueOf(record.get(0).trim()), Integer.valueOf(record.get(3).trim()));
            updateOrPutSong(song);
        }
    }

    public void updateOrPutSong(Song song) {
        if (CurrentPlaylist.containsKey(song))
            CurrentPlaylist.replace(song.getId(), song);
        else {
            CurrentPlaylist.put(song.getId(), song);
        }
    }

    public void handleNewPlaylist(byte[] data) throws IOException {
        //StringReader buffer= new StringReader(data.toString());
        log.info("Parsing new Playlist");
        Reader targetReader = new InputStreamReader(new ByteArrayInputStream(data));
        parser = new CSVParser(targetReader, CSVFormat.DEFAULT.withRecordSeparator(separator));
        createPlaylist(parser.getRecords());
        targetReader.close();
    }
}
