package com.ykw.bluetoothapp.bluetooth;

import android.annotation.TargetApi;
import android.app.Activity;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothServerSocket;
import android.bluetooth.BluetoothSocket;
import android.bluetooth.le.ScanCallback;
import android.content.Context;
import android.os.Build;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.os.Parcelable;
import android.util.Log;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.ArrayList;
import java.util.Set;
import java.util.UUID;

import static com.ykw.bluetoothapp.bluetooth.BluetoothState.DEVICE_NAME;
import static com.ykw.bluetoothapp.bluetooth.BluetoothState.INSECURE_BT_UUID;
import static com.ykw.bluetoothapp.bluetooth.BluetoothState.INSECURE_NAME;
import static com.ykw.bluetoothapp.bluetooth.BluetoothState.MESSAGE_DEVICE_NAME;
import static com.ykw.bluetoothapp.bluetooth.BluetoothState.MESSAGE_READ;
import static com.ykw.bluetoothapp.bluetooth.BluetoothState.MESSAGE_STATE_CHANGE;
import static com.ykw.bluetoothapp.bluetooth.BluetoothState.MESSAGE_TOAST;
import static com.ykw.bluetoothapp.bluetooth.BluetoothState.SECURE_BT_UUID;
import static com.ykw.bluetoothapp.bluetooth.BluetoothState.SECURE_NAME;
import static com.ykw.bluetoothapp.bluetooth.BluetoothState.STATE_CONNECTED;
import static com.ykw.bluetoothapp.bluetooth.BluetoothState.STATE_CONNECTING;
import static com.ykw.bluetoothapp.bluetooth.BluetoothState.STATE_LISTEN;
import static com.ykw.bluetoothapp.bluetooth.BluetoothState.STATE_NONE;
import static com.ykw.bluetoothapp.bluetooth.BluetoothState.TOAST;

/**
 * Created by dbsrh on 2017-11-27.
 */

public class BluetoothManager {


    private int mState;
    private int mNewState;
    private static final UUID INSECURE_UUID = UUID.fromString(INSECURE_BT_UUID);
    private static final UUID SECURE_UUID = UUID.fromString(SECURE_BT_UUID);
    private static BluetoothAdapter mBluetoothAdapter = null;
    private static final String TAG = BluetoothManager.class.getSimpleName();
    private ConnectThread connectThread;
    private ConnectedThread connectedThread;
    private AcceptThread secure_acceptThread;
    private AcceptThread in_secure_acceptThread;
    private Handler handler;

    public BluetoothManager(Context context, Handler handler){
        mBluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
        this.handler = handler;
        mState = STATE_NONE;
    }

    //Check this device supports bluetooth
    public boolean isSupportDevice(){
        return (BluetoothAdapter.getDefaultAdapter() != null);
    }

    public int getBluetoothState(){
        return mBluetoothAdapter.getState();
    }

    public int getBluetoothScanMode(){
        return mBluetoothAdapter.getScanMode();
    }
    private BluetoothAdapter getBluetoothAdapter() {
        if(mBluetoothAdapter == null){
            mBluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
        }
        return mBluetoothAdapter;
    }

    public boolean isBluetoothEnabled(){
        return mBluetoothAdapter.isEnabled();
    }

    //Flag : true - Start scanning ; Flag : false - Stop scanning
    public synchronized void Scanning(boolean flag){
        if(flag){
            if(!mBluetoothAdapter.isDiscovering()){
                mBluetoothAdapter.startDiscovery();
            }
        }else{
            if(mBluetoothAdapter.isDiscovering()){
                mBluetoothAdapter.cancelDiscovery();
            }
        }
    }


    private synchronized void updateUserInterfaceTitle(){
        mState = getState();
        mNewState = mState;
        handler.obtainMessage(MESSAGE_STATE_CHANGE, mNewState, -1).sendToTarget();
    }

    public synchronized int getState() {
        return mState;
    }

    public synchronized void start(){
        Log.d(TAG, "Start");
        if(connectThread != null){
            connectThread.cancel();
            connectThread = null;
        }

        if(connectedThread != null){
            connectedThread.cancel();
            connectedThread = null;
        }

        if(secure_acceptThread == null){
            secure_acceptThread = new AcceptThread(true);
            secure_acceptThread.start();
        }

        if(in_secure_acceptThread == null){
            in_secure_acceptThread = new AcceptThread(true);
            in_secure_acceptThread.start();
        }
        updateUserInterfaceTitle();
    }

    public synchronized void stop(){
        Log.d(TAG, "stop");
        if(connectThread != null){
            connectThread.cancel();
            connectThread = null;
        }

        if(connectedThread != null){
            connectedThread.cancel();
            connectedThread = null;
        }

        if(secure_acceptThread != null){
            secure_acceptThread.cancel();
            secure_acceptThread = null;
        }

        if(in_secure_acceptThread != null){
            in_secure_acceptThread.cancel();
            in_secure_acceptThread = null;
        }
        mState = STATE_NONE;
        updateUserInterfaceTitle();
    }

    public void write(byte[] bytes) {
        if(mState == STATE_CONNECTED){
            connectedThread.write(bytes);
        }
    }

        public synchronized void ConnectDevice(BluetoothDevice device, boolean secure){
        if(mState == STATE_CONNECTING){
            if(connectThread != null){
                connectThread.cancel();
                connectThread = null;
            }
        }
        if(connectedThread != null){
            connectedThread.cancel();
            connectedThread = null;
        }

        connectThread = new ConnectThread(device, secure);
        connectThread.start();

        updateUserInterfaceTitle();
    }

    public synchronized void manageConnectedSocket(BluetoothSocket socket, BluetoothDevice device, final String socketType){
        Log.d(TAG, "connected");

        if(connectThread != null){
            connectThread.cancel();
            connectThread = null;
        }
        if(connectedThread != null){
            connectedThread.cancel();
            connectedThread = null;
        }
        if(secure_acceptThread != null){
            secure_acceptThread.cancel();
            secure_acceptThread = null;
        }

        if(in_secure_acceptThread != null){
            in_secure_acceptThread.cancel();
            in_secure_acceptThread = null;
        }
        connectedThread = new ConnectedThread(socket, socketType);
        connectedThread.start();

        Message msg = handler.obtainMessage(MESSAGE_DEVICE_NAME);
        Bundle bundle = new Bundle();
        bundle.putString(DEVICE_NAME, device.getName());
        msg.setData(bundle);
        handler.sendMessage(msg);

        updateUserInterfaceTitle();
    }

    private void connectionFailed(){
        Message msg = handler.obtainMessage(MESSAGE_TOAST);
        Bundle bundle = new Bundle();
        bundle.putString(TOAST, "Unable to connect device");
        msg.setData(bundle);
        handler.sendMessage(msg);

        mState = STATE_NONE;
        updateUserInterfaceTitle();
        BluetoothManager.this.start();
    }

    private void connectionLost(){
        Message msg = handler.obtainMessage(MESSAGE_TOAST);
        Bundle bundle = new Bundle();
        bundle.putString(TOAST, "Device connection was lost");
        msg.setData(bundle);
        handler.sendMessage(msg);

        mState = STATE_NONE;
        updateUserInterfaceTitle();
        BluetoothManager.this.start();
    }

    private class AcceptThread extends Thread {
        private final BluetoothServerSocket server_socket;
        private String mSocketType;

        public AcceptThread(boolean secure) {
            BluetoothServerSocket tmp = null;
            mSocketType = secure ? "Secure" : "Insecure";
            try {
                if (secure) {
                    tmp = mBluetoothAdapter.listenUsingRfcommWithServiceRecord(
                            SECURE_NAME,
                            SECURE_UUID
                    );
                }else{
                    tmp = mBluetoothAdapter.listenUsingInsecureRfcommWithServiceRecord(
                            INSECURE_NAME,
                            INSECURE_UUID
                    );
                }
            } catch (IOException e) {
                Log.e(TAG, "Socket Type: " + mSocketType + "listen() failed", e);
            }
            server_socket = tmp;
            mState = STATE_LISTEN;
        }

        @Override
        public void run() {
            Log.d(TAG, "Socket Type: " + mSocketType + "BEGIN AcceptThread" + this);
            setName("AcceptThread"+mSocketType);
            BluetoothSocket socket = null;
            while(mState != STATE_CONNECTED){
                try{
                    socket = server_socket.accept();
                } catch (IOException e) {
                    Log.e(TAG, "Socket Type: " + mSocketType + "accept() failed", e);
                    break;
                }

                if(socket != null){
                    synchronized (BluetoothManager.this){
                        switch (mState){
                            case STATE_LISTEN:
                            case STATE_CONNECTING:
                                manageConnectedSocket(socket, socket.getRemoteDevice(),
                                        mSocketType);
                                break;
                            case STATE_NONE:
                            case STATE_CONNECTED:
                                try{
                                    socket.close();
                                } catch (IOException e) {
                                    Log.e(TAG, "Could not close unwanted socket", e);
                                }
                                break;
                        }
                    }
                }
            }
            Log.i(TAG, "END acceptThread, socket Type:" + mSocketType);
        }

        public void cancel(){
            Log.d(TAG, "Socket Type" + mSocketType + "cancel " + this);
            try{
                server_socket.close();
            } catch (IOException e) {
                Log.e(TAG, "Socket Type" + mSocketType + "close() of server failed", e);
            }
        }
    }

    private class ConnectThread extends Thread{
        private final BluetoothSocket mmSocket;
        private final BluetoothDevice mmDevice;
        private String mSocketType;

        private ConnectThread(BluetoothDevice device, boolean secure) {
            mmDevice = device;
            BluetoothSocket tmp = null;
            mSocketType = secure ? "Secure" : "Insecure";
            try{
                if(secure){
                    tmp = device.createRfcommSocketToServiceRecord(SECURE_UUID);
                }else{
                    tmp = device.createInsecureRfcommSocketToServiceRecord(INSECURE_UUID);
                }
            }catch(IOException e){
                Log.d(TAG, "Socket Type:" + mSocketType + "create() failed", e);
            }
            mmSocket = tmp;
            mState = STATE_CONNECTING;
        }

        @Override
        public void run() {
            setName("ConnectThread"+mSocketType);
            Scanning(false);

            try{
                mmSocket.connect();
            }catch(IOException connectionException){
                try{
                    mmSocket.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
                connectionFailed();
                return;
            }
            synchronized (BluetoothManager.this){
                connectThread = null;
            }
            manageConnectedSocket(mmSocket, mmDevice, mSocketType);
        }

        public void cancel(){
            try{
                mmSocket.close();
            }catch(IOException e){
                Log.d(TAG, "close() of connect " + mSocketType + "socket failed ", e);
            }
        }
    }

    private class ConnectedThread extends Thread{
        private final BluetoothSocket mmSocket;
        private final InputStream mmInStream;
        private final OutputStream mmOutStream;

        public ConnectedThread(BluetoothSocket socket, String socketType){
            Log.d(TAG, "create ConnectedThread: " + socketType);
            mmSocket = socket;
            InputStream tmpIn = null;
            OutputStream tmpOut = null;

            try{
                tmpIn = socket.getInputStream();
                tmpOut = socket.getOutputStream();
            } catch (IOException e) {
                Log.d(TAG, "Exception Occur");
                e.printStackTrace();
            }
            mmInStream = tmpIn;
            mmOutStream = tmpOut;
            mState = STATE_CONNECTED;
        }

        @Override
        public void run() {
            super.run();
            byte[] buffer = new byte[512];
            int bytes = 0, data;

            while(mState == STATE_CONNECTED){
                try{
                    while((data = mmInStream.read()) != 0x0D){
                        if(data != 0x0A){
                            buffer[bytes] = (byte)data;
                            bytes++;
                        }
                    }
                    //bytes = mmInStream.read(buffer);

                    handler.obtainMessage(MESSAGE_READ, bytes, -1, buffer)
                    .sendToTarget();
                    bytes = 0;
                } catch (IOException e) {
                    Log.d(TAG, "disconnected", e);
                    connectionLost();
                    break;
                }
            }
        }

        public void write(byte[] bytes){
            try{
                mmOutStream.write(bytes);
            } catch (IOException e) {
                Log.d(TAG, "Exception Occur");
                e.printStackTrace();
            }
        }

        public void cancel(){
            try{
                mmSocket.close();
            } catch (IOException e) {
                Log.d(TAG, "close() of connect socket failed", e);
            }
        }
    }
}
