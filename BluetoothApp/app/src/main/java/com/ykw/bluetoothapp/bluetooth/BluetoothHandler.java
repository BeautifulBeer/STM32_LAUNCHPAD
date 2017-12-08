package com.ykw.bluetoothapp.bluetooth;

import android.content.Context;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import static com.ykw.bluetoothapp.bluetooth.BluetoothState.MESSAGE_READ;

/**
 * Created by dbsrh on 2017-11-29.
 */

public class BluetoothHandler extends Handler {

    private static final String TAG = BluetoothHandler.class.getSimpleName();

    @Override
    public void handleMessage(Message msg) {
        if(msg.what == MESSAGE_READ){
            Log.d(TAG, msg.obj.toString());
        }
    }
}
