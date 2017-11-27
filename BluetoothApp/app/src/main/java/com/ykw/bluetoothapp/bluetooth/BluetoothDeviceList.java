package com.ykw.bluetoothapp.bluetooth;

import android.annotation.SuppressLint;
import android.bluetooth.BluetoothDevice;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.os.Bundle;
import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.ListView;
import android.widget.TextView;

import com.ykw.bluetoothapp.R;

import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;
import java.util.List;

/**
 * Created by dbsrh on 2017-11-27.
 */

public class BluetoothDeviceList extends AppCompatActivity{

    private BluetoothManager manager;
    private ArrayList<BluetoothDeviceList.DeviceInformation> paired_devices = null;
    private DeviceListAdapter adapter = null;
    private ListView listView;
    private final BroadcastReceiver mReceiver = new BroadcastReceiver() {
        @Override
        public void onReceive(Context context, Intent intent) {
            String action = intent.getAction();
            if(BluetoothDevice.ACTION_FOUND.equals(action)){
                BluetoothDevice device = intent.getParcelableExtra(BluetoothDevice.EXTRA_DEVICE);
                BluetoothDeviceList.DeviceInformation information = new BluetoothDeviceList.DeviceInformation(
                        device.getName(),
                        device.getAddress());
                paired_devices.add(0, information);
                if(adapter != null)adapter.notifyDataSetChanged();
            }
        }
    };
    private static final String TAG = BluetoothDeviceList.class.getSimpleName();

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.device_list_layout);
        listView = (ListView)findViewById(R.id.device_list);
        manager = BluetoothManager.getInstance();
        paired_devices = new ArrayList<>();
        manager.getPairedDevices(paired_devices);
        adapter = new DeviceListAdapter(this, R.layout.device_list_item, paired_devices);
        listView.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> adapterView, View view, int position, long l) {
                //Address get
                ((DeviceListAdapter)adapterView.getAdapter())
                        .getItemAtPosition(position).getAddress();
            }
        });
        listView.setAdapter(adapter);
    }

    @Override
    protected void onStart() {
        super.onStart();
        IntentFilter filter = new IntentFilter(BluetoothDevice.ACTION_FOUND);
        registerReceiver(mReceiver, filter);
    }

    @Override
    protected void onStop() {
        super.onStop();
        unregisterReceiver(mReceiver);
    }

    private class DeviceListAdapter extends ArrayAdapter<DeviceInformation>{

        private ArrayList<DeviceInformation> arrayList = new ArrayList<>();


        public DeviceListAdapter(@NonNull Context context, int resource, @NonNull ArrayList<DeviceInformation> objects) {
            super(context, resource, objects);
            arrayList = objects;
        }

        @SuppressLint("ViewHolder")
        @NonNull
        @Override
        public View getView(int position, @Nullable View convertView, @NonNull ViewGroup parent) {
            if (((LayoutInflater)getContext().getSystemService(Context.LAYOUT_INFLATER_SERVICE)
                    ) != null) {
                convertView = ((LayoutInflater)getContext().getSystemService(Context.LAYOUT_INFLATER_SERVICE)
                        ).inflate(R.layout.device_layout_text, parent);
            }
            ((TextView)convertView.findViewById(R.id.device_name)).setText(arrayList.get(position).getName());
            ((TextView)convertView.findViewById(R.id.device_addr)).setText(arrayList.get(position).getAddress());
            return convertView;
        }

        @Override
        public int getCount() {
            return arrayList.size();
        }

        public DeviceInformation getItemAtPosition(int position){
            return arrayList.get(position);
        }

    }

    public static class DeviceInformation{
        String name;
        String address;

        public DeviceInformation(String name, String addr){
            this.name = name;
            this.address = addr;
        }

        public String getName() {
            return name;
        }

        public void setName(String name) {
            this.name = name;
        }

        public String getAddress() {
            return address;
        }

        public void setAddress(String address) {
            this.address = address;
        }
    }
}
