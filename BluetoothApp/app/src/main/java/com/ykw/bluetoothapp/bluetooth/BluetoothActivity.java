package com.ykw.bluetoothapp.bluetooth;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.content.Context;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.media.AudioManager;
import android.media.MediaPlayer;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.os.Message;
import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;

import com.ykw.bluetoothapp.MusicPlay.MediaPlayerManager;
import com.ykw.bluetoothapp.MusicPlay.MusicResourceManager;
import com.ykw.bluetoothapp.MusicPlay.SoundsPoolManager;
import com.ykw.bluetoothapp.R;

import java.io.IOException;
import java.io.UnsupportedEncodingException;
import java.util.Timer;
import java.util.TimerTask;

import static android.Manifest.permission.ACCESS_COARSE_LOCATION;
import static android.Manifest.permission.ACCESS_FINE_LOCATION;
import static android.support.v4.content.PermissionChecker.PERMISSION_GRANTED;
import static com.ykw.bluetoothapp.bluetooth.BluetoothState.CARRAIGE_RETURN;
import static com.ykw.bluetoothapp.bluetooth.BluetoothState.DEVICE_NAME;
import static com.ykw.bluetoothapp.bluetooth.BluetoothState.EXTRA_DEVICE_ADDRESS;
import static com.ykw.bluetoothapp.bluetooth.BluetoothState.LINE_FEED;
import static com.ykw.bluetoothapp.bluetooth.BluetoothState.MESSAGE_DEVICE_NAME;
import static com.ykw.bluetoothapp.bluetooth.BluetoothState.MESSAGE_READ;
import static com.ykw.bluetoothapp.bluetooth.BluetoothState.MESSAGE_TOAST;
import static com.ykw.bluetoothapp.bluetooth.BluetoothState.MUSIC_PLAY;
import static com.ykw.bluetoothapp.bluetooth.BluetoothState.REQUEST_ENABLE_DEVICE;
import static com.ykw.bluetoothapp.bluetooth.BluetoothState.REQUEST_PERMISSION;
import static com.ykw.bluetoothapp.bluetooth.BluetoothState.STATE_CONNECTED;
import static com.ykw.bluetoothapp.bluetooth.BluetoothState.SYSTEM_START;
import static com.ykw.bluetoothapp.bluetooth.BluetoothState.TOAST;

/**
 * Created by dbsrh on 2017-11-27.
 */

public class BluetoothActivity extends AppCompatActivity
    implements BluetoothActivityInterface {

    private Button connect_btn_;
    private Button play1_btn_;
    private BluetoothManager manager;
    private Handler handler;
    private BluetoothAdapter mBluetoothAdapter = null;
    private MediaPlayerManager mediaPlayerManager;
    private AudioManager audioManager;
    private static final int StreamType = AudioManager.STREAM_MUSIC;
    private static final String TAG = BluetoothActivity.class.getSimpleName();
    private TimerTask timerTask;
    private Timer timer;
    private byte[] requestMusic;
    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.bluetooth_activity);
        connect_btn_ = (Button)findViewById(R.id.connect_btn);
        play1_btn_ = (Button)findViewById(R.id.play1_btn);
        mediaPlayerManager = MediaPlayerManager.getInstance(getApplicationContext());
        final byte[] requestMusic = new byte[3];
        requestMusic[0] = MUSIC_PLAY;
        requestMusic[1] = CARRAIGE_RETURN;
        requestMusic[2] = LINE_FEED;
        timerTask = new TimerTask() {
            @Override
            public void run() {
                manager.write(requestMusic);
            }
        };
        timer = new Timer();
        timer.schedule(timerTask, 3000, 4000);
        handler = new Handler(Looper.getMainLooper()){
            @Override
            public void handleMessage(Message msg) {
                if(msg.what == MESSAGE_DEVICE_NAME){
                    String device_name = msg.getData().getString(DEVICE_NAME);
                    setTitle(device_name);
                }else if(msg.what == MESSAGE_TOAST){
                    Toast.makeText(getApplicationContext(), msg.getData().getString(TOAST),Toast.LENGTH_LONG).show();
                }else if(msg.what == MESSAGE_READ){
                    int bytes = msg.arg1;
                    byte[] buffer = (byte[])msg.obj;
                    if(buffer == null){
                        Log.d(TAG, "NULL");
                    }else{
                        try {
                            String data = new String(buffer, 0, bytes, "UTF-8");
                            if(!data.equals("")){
                                Log.d(TAG, "DATA : "+data);
                                if(data.length() >= 3){
                                    if(data.charAt(0) == 'b'){
                                        if((data.charAt(1) - '0') == 1){
                                            mediaPlayerManager.play(2);
                                        }
                                        if((data.charAt(2) - '0') == 1){
                                            mediaPlayerManager.play(3);
                                        }
                                }
                                }else if(data.charAt(0) == 'm'){
                                    if(data.length() >= 2){
                                        Log.d(TAG, "dd : " + data.charAt(1));
                                        mediaPlayerManager.play((data.charAt(1) - '0'));
                                    }
                                }else if(data.charAt(0) == 'v'){
                                    if(data.length() >= 2){
                                        if((data.charAt(1) - '0') == 1){
                                            VolumeUP();
                                        }else if((data.charAt(1) - '0') == 0){
                                            VolumeDOWN();
                                        }
                                    }
                                }
                            }
                        } catch (UnsupportedEncodingException e) {
                            e.printStackTrace();
                        } catch (IOException e) {
                            e.printStackTrace();
                        }
                    }

                }
            }
        };
        mBluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
        manager = new BluetoothManager(this, handler);
        VolumeZero();
        enableDiscovering();
        checkPermission();
        connect_btn_.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if(manager.isSupportDevice()){
                    Intent intent = new Intent(BluetoothActivity.this, BluetoothDeviceList.class);
                    startActivityForResult(intent, REQUEST_ENABLE_DEVICE);
                }else{
                    Toast.makeText(getApplicationContext(), "This device do not support bluetooth", Toast.LENGTH_SHORT)
                            .show();
                }
            }
        });

        play1_btn_.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                byte[] buf = new byte[3];
                buf[0] = SYSTEM_START;
                buf[1] = CARRAIGE_RETURN;
                buf[2] = LINE_FEED;
                manager.write(buf);
            }
        });
    }

    @Override
    protected void onStart() {
        super.onStart();
        if(!manager.isBluetoothEnabled()){
            activateBluetooth();
        }
    }

    @Override
    protected void onStop() {
        super.onStop();
    }

    @Override
    public void activateBluetooth() {
        Intent enableBtIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
        startActivityForResult(enableBtIntent, BluetoothState.REQUEST_ENABLE_BT);
    }

    public void enableDiscovering(){
        if(mBluetoothAdapter.getScanMode() !=
                BluetoothAdapter.SCAN_MODE_CONNECTABLE_DISCOVERABLE){
            Intent discoverableIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_DISCOVERABLE);
            discoverableIntent.putExtra(BluetoothAdapter.EXTRA_DISCOVERABLE_DURATION, 300);
            startActivity(discoverableIntent);
        }
    }

    public void checkPermission(){
        String permissions = "";
        if(checkSelfPermission(ACCESS_COARSE_LOCATION) != PackageManager.PERMISSION_GRANTED) {
            permissions += ACCESS_COARSE_LOCATION;
        }
        if(checkSelfPermission(ACCESS_FINE_LOCATION) != PackageManager.PERMISSION_GRANTED){
            permissions += "," + ACCESS_FINE_LOCATION;
        }
        if(!permissions.equals("")) {
            this.requestPermissions(
                    permissions.split(","),
                    REQUEST_PERMISSION);
        }
    }


    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        if(requestCode == BluetoothState.REQUEST_ENABLE_BT){
            if(resultCode == RESULT_CANCELED){
                Toast.makeText(getApplicationContext(), "Cannot use this application without bluetooth", Toast.LENGTH_LONG)
                        .show();
                finish();
            }
        }else if(requestCode == REQUEST_ENABLE_DEVICE){
            if(resultCode == RESULT_OK){
                connectDevice(data, false);
            }
        }
    }

    @Override
    public void onRequestPermissionsResult(int requestCode, @NonNull String[] permissions, @NonNull int[] grantResults) {
        if(requestCode == REQUEST_PERMISSION){
            if(grantResults[0] == PERMISSION_GRANTED){
                activateBluetooth();
            }else{
                Toast.makeText(this, "Cannot use this application without location permission", Toast.LENGTH_LONG)
                .show();
                finish();
            }
        }
    }

    public void connectDevice(Intent data, boolean secure){
        String address = data.getExtras()
                .getString(EXTRA_DEVICE_ADDRESS);
        BluetoothDevice device = mBluetoothAdapter.getRemoteDevice(address);
        manager.ConnectDevice(device, secure);
    }

    public void VolumeZero(){
        audioManager = (AudioManager)getSystemService(Context.AUDIO_SERVICE);
        audioManager.setStreamVolume(StreamType, 0, AudioManager.FLAG_PLAY_SOUND);
    }

    public void VolumeUP(){
        audioManager = (AudioManager)getSystemService(Context.AUDIO_SERVICE);
        int currVol = audioManager.getStreamVolume(StreamType);
        int maxVol = audioManager.getStreamMaxVolume(StreamType);
        if(currVol < maxVol - 1){
            audioManager.setStreamVolume(StreamType, currVol +2, AudioManager.FLAG_PLAY_SOUND);
        }
    }

    public void VolumeDOWN(){
        audioManager = (AudioManager)getSystemService(Context.AUDIO_SERVICE);
        int currVol = audioManager.getStreamVolume(StreamType);
        if(currVol > 1){
            audioManager.setStreamVolume(StreamType, currVol -2, AudioManager.FLAG_PLAY_SOUND);
        }
    }
}

