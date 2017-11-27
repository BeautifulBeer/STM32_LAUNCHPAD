package com.ykw.bluetoothapp.bluetooth;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.util.Log;

import java.io.IOException;
import java.util.ArrayList;
import java.util.Set;
import java.util.UUID;

/**
 * Created by dbsrh on 2017-11-27.
 */

public class BluetoothManager {
    private static final UUID bt_UUID = UUID.randomUUID();
    private static BluetoothAdapter mBluetoothAdapter = null;
    private static final String TAG = BluetoothManager.class.getSimpleName();

    public static BluetoothManager getInstance(){
        return new BluetoothManager();
    }

    private BluetoothManager(){
        mBluetoothAdapter = getBluetoothAdapter();
    }

    //Check this device supports bluetooth
    public boolean isSupportDevice(){
        return (BluetoothAdapter.getDefaultAdapter() != null);
    }

    public BluetoothAdapter getBluetoothAdapter() {
        if(mBluetoothAdapter == null){
            mBluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
        }
        return mBluetoothAdapter;
    }

    public void getPairedDevices(ArrayList<BluetoothDeviceList.DeviceInformation> arrayList){
        Set<BluetoothDevice> pairedDevices = mBluetoothAdapter.getBondedDevices();
        if (pairedDevices.size() > 0){
            for (BluetoothDevice device : pairedDevices){
                BluetoothDeviceList.DeviceInformation deviceInformation = new BluetoothDeviceList.DeviceInformation(
                        device.getName(),
                        device.getAddress());
                arrayList.add(deviceInformation);
            }
        }
    }

    public void ScanningDevices(){

    }

    public void ConnectDevice(String name, String address){

    }

    private class ConnectThread extends Thread{
        private final BluetoothSocket mmSocket;
        private final BluetoothDevice mmDevice;

        private final String TAG = ConnectThread.class.getSimpleName();

        private ConnectThread(BluetoothDevice device) {
            mmDevice = device;
            BluetoothSocket tmp = null;

            try{
                tmp = device.createRfcommSocketToServiceRecord(bt_UUID);
            }catch(IOException e){
                Log.d(TAG, bt_UUID.toString() + " : " + e.toString());
            }
            mmSocket = tmp;
        }

        @Override
        public void run() {
            super.run();
            BluetoothAdapter adapter = getBluetoothAdapter();
            adapter.cancelDiscovery();

        }
    }
}
