package com.ykw.bluetoothapp.MusicPlay;

import android.content.Context;
import android.media.MediaPlayer;
import android.net.Uri;
import android.util.Log;

import com.ykw.bluetoothapp.Pool;

import java.io.IOException;

/**
 * Created by dbsrh on 2017-12-02.
 */

public class MediaPlayerManager {
    private static MediaPlayerManager mediaPlayerManager;
    private Context context;
    private Pool<MediaPlayer> mediaPlayerPool;
    private final int max_PoolSize = 3;
    private final String TAG = MediaPlayerManager.class.getSimpleName();
    int test = 0;

    private MediaPlayerManager(Context context) {
        this.context = context;
        if (mediaPlayerPool == null) {
            mediaPlayerPool = new Pool<>(max_PoolSize);
        }
        for(int i=0; i<max_PoolSize; i++){
            MediaPlayer mediaPlayer = new MediaPlayer();
            mediaPlayer.setOnCompletionListener(new MediaPlayer.OnCompletionListener() {
                @Override
                public void onCompletion(MediaPlayer mediaPlayer) {
                    if(mediaPlayer != null){
                        mediaPlayer.reset();
                        Log.d(TAG, "Media comeback");
                    }
                    mediaPlayerPool.add(mediaPlayer);
                }
            });
            mediaPlayer.setOnPreparedListener(new MediaPlayer.OnPreparedListener() {
                @Override
                public void onPrepared(MediaPlayer mediaPlayer) {
                    mediaPlayer.start();
                }
            });
            mediaPlayerPool.add(mediaPlayer);
        }
    }

    public static MediaPlayerManager getInstance(Context context){
        if(mediaPlayerManager == null){
            mediaPlayerManager = new MediaPlayerManager(context);
        }
        return mediaPlayerManager;
    }

    public void play(int index) throws IOException {
        MediaPlayer player = mediaPlayerPool.get();
        if (player != null) {
            Log.d(TAG, "Media played");
            Uri uri = MusicResourceManager.getInstance(context).getMusicUri(index);
            Log.d(TAG, uri.toString());
            player.setDataSource(context,
                    uri);
            player.prepareAsync();
        }
    }

    public Pool<MediaPlayer> getMediaPlayerPool() {
        return mediaPlayerPool;
    }
}
