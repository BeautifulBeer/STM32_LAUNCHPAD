package com.ykw.bluetoothapp;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

import app.akexorcist.bluetotohspp.library.BluetoothSPP;
import app.akexorcist.bluetotohspp.library.BluetoothState;

/**
 * Created by dbsrh on 2017-11-25.
 */

public class BluetoothActivity extends AppCompatActivity{
    private TextView connected_device_name_;
    private TextView connected_device_addr_;
    private Button connection_btn_;
    private Button play_btn_;
    private BluetoothSPP bt;

    private static final String TAG = BluetoothActivity.class.getSimpleName();

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.bluetooth_activity);

        connected_device_name_ = (TextView)findViewById(R.id.device_name);
        connected_device_addr_ = (TextView)findViewById(R.id.device_addr);
        connection_btn_ = (Button)findViewById(R.id.connect_btn);
        play_btn_ = (Button)findViewById(R.id.play_btn);


        bt = new BluetoothSPP(this);

        connection_btn_.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if(!bt.isBluetoothAvailable()){
                    Toast.makeText(view.getContext(), "Cannot use Bluetooth", Toast.LENGTH_SHORT).show();
                }else {
                    if (bt.getServiceState() == BluetoothState.STATE_CONNECTED) {
                        bt.disconnect();
                    } else {
                        Intent intent = new Intent(getApplicationContext(), DeviceList.class);
                        intent.putExtra("bluetooth_devices", "Bluetooth Devices");
                        intent.putExtra("no_devices_found", "No device");
                        intent.putExtra("scanning", "Scanning");
                        intent.putExtra("scan_for_devices", "Search");
                        intent.putExtra("select_device", "Select");
                        intent.putExtra("layout_list", R.layout.device_layout_list);
                        intent.putExtra("layout_text", R.layout.device_layout_text);
                        startActivityForResult(intent, BluetoothState.REQUEST_CONNECT_DEVICE);
                    }
                }
            }
        });

        bt.setOnDataReceivedListener(new BluetoothSPP.OnDataReceivedListener() {
            @Override
            public void onDataReceived(byte[] data, String message) {
                Log.i(TAG, "dmdLength : " + data.length);
                Log.i(TAG, "Message : " + message);
            }
        });

        bt.setBluetoothConnectionListener(new BluetoothSPP.BluetoothConnectionListener() {
            @Override
            public void onDeviceConnected(String name, String address) {

            }

            @Override
            public void onDeviceDisconnected() {

            }

            @Override
            public void onDeviceConnectionFailed() {

            }
        });

        bt.setBluetoothStateListener(new BluetoothSPP.BluetoothStateListener() {
            @Override
            public void onServiceStateChanged(int state) {
                String state_str = "NONE_OF_THEM";
                switch (state) {
                    case BluetoothState.STATE_CONNECTED:
                        state_str = "STATE_CONNECTED";
                        break;
                    case BluetoothState.STATE_CONNECTING:
                        state_str = "STATE_CONNECTING";
                        break;
                    case BluetoothState.STATE_LISTEN:
                        state_str = "STATE_LISTEN";
                        break;
                    case BluetoothState.STATE_NONE:
                        state_str = "STATE_NONE";
                        break;
                    case BluetoothState.STATE_NULL:
                        state_str = "STATE_NULL";
                        break;
                }
                Log.d(TAG, state_str);
            }
        });
    }

    @Override
    protected void onStart() {
        super.onStart();
        if(!bt.isBluetoothEnabled()){
            Log.d(TAG, "Bluetooth is not available");
            bt.enable();
        }else{
            if(bt.isServiceAvailable()){
                bt.setupService();
                bt.startService(BluetoothState.DEVICE_OTHER);
            }
        }
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        bt.stopService();
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        if(requestCode == BluetoothState.REQUEST_CONNECT_DEVICE){
            if(resultCode == Activity.RESULT_OK){
                if(!bt.isServiceAvailable()){
                    bt.setupService();
                }
                bt.connect(data);
            }
        }else if(requestCode == BluetoothState.REQUEST_ENABLE_BT){
            if(resultCode == Activity.RESULT_OK){
                bt.setupService();
            }else{
                Toast.makeText(this, "블루투스를 허용해야 앱 사용이 가능합니다.", Toast.LENGTH_SHORT)
                        .show();
                finish();
            }
        }
    }
}
