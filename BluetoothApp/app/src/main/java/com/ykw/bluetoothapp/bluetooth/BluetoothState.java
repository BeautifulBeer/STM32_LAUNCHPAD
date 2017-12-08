package com.ykw.bluetoothapp.bluetooth;

/**
 * Created by dbsrh on 2017-11-27.
 */

public interface BluetoothState {

    public static final String SECURE_NAME = "MON_TEAM3_SECURE";
    public static final String INSECURE_NAME = "MON_TEAM3_INSECURE";
    //bluetooth specification 128bit without dashes
    public static final String SECURE_BT_UUID = "5948296a-bf29-13bb-c594-01dd5ab51025";
    public static final String INSECURE_BT_UUID = "00544698-051a-b539-d544-a0000a0b5697";

    //Intent State
    public static final int REQUEST_ENABLE_BT = 1;
    public static final int REQUEST_ENABLE_DEVICE = 2;
    public static final int REQUEST_PERMISSION = 3;

    //Handler State
    public static final int MESSAGE_READ = 1;
    public static final int MESSAGE_DEVICE_NAME = 2;
    public static final int MESSAGE_DEVICE_ADDR = 3;
    public static final int MESSAGE_STATE_CHANGE = 4;
    public static final int MESSAGE_TOAST = 5;


    public static final String DEVICE_NAME = "device_name";
    public static final String TOAST = "toast";
    public static final String EXTRA_DEVICE_ADDRESS = "extra_address";

    //Bluetooth State
    public static final int STATE_NONE = 1;
    public static final int STATE_CONNECTED = 2;
    public static final int STATE_CONNECTING = 3;
    public static final int STATE_LISTEN = 4;

}
