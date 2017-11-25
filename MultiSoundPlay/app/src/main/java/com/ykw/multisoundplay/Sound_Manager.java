package com.ykw.multisoundplay;

import android.media.AudioManager;
import android.media.MediaPlayer;

/**
 * Created by dbsrh on 2017-11-07.
 */

public class Sound_Manager {
    private MediaPlayer mediaPlayer;

    public Sound_Manager(){
        mediaPlayer = new MediaPlayer();

    }

}

/*    SoundPool soundPool;
    HashMap<String, Integer> sounds;

    public Sound_Manager(int sound_cnt){
        AudioAttributes audioAttributes = new AudioAttributes.Builder()
                //Specify content-type
                .setContentType(AudioAttributes.CONTENT_TYPE_MUSIC)
                //Specify usage
                .setUsage(AudioAttributes.USAGE_MEDIA)
                //Systemically to ensure music playing
                .setFlags(AudioAttributes.FLAG_AUDIBILITY_ENFORCED)
                .setLegacyStreamType(AudioManager.STREAM_MUSIC)
                .build();

        soundPool = new SoundPool.Builder()
                .setMaxStreams(sound_cnt)
                .setAudioAttributes(audioAttributes)
                .build();

        sounds = new HashMap<String, Integer>();
    }

    public void destroy(){

    }*/