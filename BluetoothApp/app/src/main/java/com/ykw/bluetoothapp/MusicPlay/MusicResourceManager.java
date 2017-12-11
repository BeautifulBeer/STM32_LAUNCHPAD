package com.ykw.bluetoothapp.MusicPlay;

import android.content.Context;
import android.content.res.Resources;
import android.net.Uri;
import android.util.SparseArray;
import android.util.SparseIntArray;

import com.ykw.bluetoothapp.R;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Vector;

/**
 * Created by dbsrh on 2017-12-01.
 */

public class MusicResourceManager {
    private static MusicResourceManager musicResourceManager;
    private static int SOUNDPOOL_SND_MUSIC1 = 0;
    private static int SOUNDPOOL_SND_MUSIC2 = 1;
    private static int SOUNDPOOL_SND_MUSIC3 = 2;
    private static int SOUNDPOOL_SND_MUSIC4 = 3;
    private static final int maxSounds = 4;

    private SparseArray<Uri> soundPoolMap;

    private MusicResourceManager(Context context){
        soundPoolMap = new SparseArray<>();
        soundPoolMap.put(SOUNDPOOL_SND_MUSIC1,
                retrieveURI(context, R.raw.music1));
        soundPoolMap.put(SOUNDPOOL_SND_MUSIC2,
                retrieveURI(context, R.raw.music2));
        soundPoolMap.put(SOUNDPOOL_SND_MUSIC3,
                retrieveURI(context, R.raw.music3));
        soundPoolMap.put(SOUNDPOOL_SND_MUSIC4,
                retrieveURI(context, R.raw.music4));
    }

    public static MusicResourceManager getInstance(Context context){
        if(musicResourceManager == null){
            musicResourceManager = new MusicResourceManager(context);
        }
        return musicResourceManager;
    }

    public Uri getMusicUri(int index){
        return soundPoolMap.get(index);
    }

    private Uri retrieveURI(Context context, int resource_id){
        return Uri.parse("android.resource://"+context.getPackageName()+"/"+resource_id);
    }

}
