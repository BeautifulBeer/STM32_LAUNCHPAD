package com.ykw.bluetoothapp.MusicPlay;

import android.app.PendingIntent;
import android.content.Context;
import android.media.AudioManager;
import android.media.SoundPool;
import android.util.SparseArray;
import android.util.SparseIntArray;

import com.ykw.bluetoothapp.R;

import java.util.ArrayList;
import java.util.HashMap;

/**
 * Created by dbsrh on 2017-12-01.
 */

public class SoundsPoolManager {

    private static int SOUNDPOOL_SND_MUSIC1 = 0;
    private static int SOUNDPOOL_SND_MUSIC2 = 1;
    private static int SOUNDPOOL_SND_MUSIC3 = 2;
    private static int SOUNDPOOL_SND_MUSIC4 = 3;

    private static SoundsPoolManager manager;
    private SoundPool soundPool;
    private SparseIntArray soundPoolMap;
    private AudioManager audioManager;
    private boolean isSoundTurnedOff;

    private static final int maxSounds = 20;


    private SoundsPoolManager(Context context){
        soundPool = new SoundPool(maxSounds, AudioManager.STREAM_MUSIC, 0);
        audioManager = (AudioManager)context.getSystemService(Context.AUDIO_SERVICE);
        soundPoolMap = new SparseIntArray();
        soundPoolMap.put(SOUNDPOOL_SND_MUSIC1, soundPool.load(context, R.raw.music1,1));
        soundPoolMap.put(SOUNDPOOL_SND_MUSIC2, soundPool.load(context, R.raw.music2,1));
        soundPoolMap.put(SOUNDPOOL_SND_MUSIC3, soundPool.load(context, R.raw.music3,1));
        soundPoolMap.put(SOUNDPOOL_SND_MUSIC4, soundPool.load(context, R.raw.music4,1));
        int streamVolume = audioManager.getStreamVolume(AudioManager.STREAM_MUSIC);
        soundPool.play(soundPoolMap.get(0), streamVolume, streamVolume, 1, 1, 1f);
        soundPool.play(soundPoolMap.get(1), streamVolume, streamVolume, 1, 1, 1f);
        soundPool.play(soundPoolMap.get(2), streamVolume, streamVolume, 1, 1, 1f);
    }

    public static SoundsPoolManager getInstance(Context context){
        if(manager == null){
            manager = new SoundsPoolManager(context);
        }
        return manager;
    }

    public void playSound(int index, int loop){
        if(maxSounds > index){
            int streamVolume = audioManager.getStreamVolume(AudioManager.STREAM_MUSIC);
            soundPool.play(soundPoolMap.get(index), streamVolume, streamVolume, 1, loop, 1f);
        }
    }


}
