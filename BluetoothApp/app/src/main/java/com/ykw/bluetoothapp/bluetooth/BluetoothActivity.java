package com.ykw.bluetoothapp.bluetooth;

import android.annotation.TargetApi;
import android.app.Activity;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.pm.PackageManager;
import android.os.Build;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.os.Message;
import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import android.support.annotation.RequiresApi;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

import com.ykw.bluetoothapp.R;

import java.util.ArrayList;

import static android.Manifest.permission.ACCESS_COARSE_LOCATION;
import static android.Manifest.permission.ACCESS_FINE_LOCATION;
import static android.support.v4.content.PermissionChecker.PERMISSION_GRANTED;
import static com.ykw.bluetoothapp.bluetooth.BluetoothState.DEVICE_NAME;
import static com.ykw.bluetoothapp.bluetooth.BluetoothState.EXTRA_DEVICE_ADDRESS;
import static com.ykw.bluetoothapp.bluetooth.BluetoothState.MESSAGE_DEVICE_NAME;
import static com.ykw.bluetoothapp.bluetooth.BluetoothState.MESSAGE_TOAST;
import static com.ykw.bluetoothapp.bluetooth.BluetoothState.REQUEST_ENABLE_DEVICE;
import static com.ykw.bluetoothapp.bluetooth.BluetoothState.REQUEST_PERMISSION;
import static com.ykw.bluetoothapp.bluetooth.BluetoothState.TOAST;

/**
 * Created by dbsrh on 2017-11-27.
 */

public class BluetoothActivity extends AppCompatActivity
    implements BluetoothActivityInterface {

    private Button connect_btn_;
    private Button start_play_btn_;
    private BluetoothManager manager;
    private Handler handler;
    private BluetoothAdapter mBluetoothAdapter = null;


    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.bluetooth_activity);
        connect_btn_ = (Button)findViewById(R.id.connect_btn);
        start_play_btn_ = (Button)findViewById(R.id.play_btn);
        handler = new Handler(Looper.getMainLooper()){
            @Override
            public void handleMessage(Message msg) {
                if(msg.what == MESSAGE_DEVICE_NAME){
                    String device_name = msg.getData().getString(DEVICE_NAME);
                    setTitle(device_name);
                }else if(msg.what == MESSAGE_TOAST){
                    Toast.makeText(getApplicationContext(), msg.getData().getString(TOAST),Toast.LENGTH_LONG).show();
                }
            }
        };
        mBluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
        manager = new BluetoothManager(this, handler);
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

        start_play_btn_.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {

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
}
