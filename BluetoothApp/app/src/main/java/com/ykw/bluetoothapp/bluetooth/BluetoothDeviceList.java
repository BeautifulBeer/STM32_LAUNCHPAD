package com.ykw.bluetoothapp.bluetooth;

import android.annotation.SuppressLint;
import android.app.Activity;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.os.Bundle;
import android.os.Handler;
import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import android.support.design.widget.FloatingActionButton;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;

import com.ykw.bluetoothapp.R;

import java.util.ArrayList;
import java.util.Set;

import static com.ykw.bluetoothapp.bluetooth.BluetoothState.EXTRA_DEVICE_ADDRESS;

/**
 * Created by dbsrh on 2017-11-27.
 */

public class BluetoothDeviceList extends AppCompatActivity{

    private FloatingActionButton search_btn;
    private BluetoothAdapter mAdapter;
    private ArrayList<BluetoothDevice> paired_devices = new ArrayList<>();
    private DeviceListAdapter adapter = null;
    private ListView listView;
    private final String CANNOT_FOUND = "CANNOT FIND ANY AROUND DEVICES";
    private final BroadcastReceiver mReceiver = new BroadcastReceiver() {
        @Override
        public void onReceive(Context context, Intent intent) {
            String action = intent.getAction();
            if(BluetoothDevice.ACTION_FOUND.equals(action)){
                BluetoothDevice device = intent.getParcelableExtra(BluetoothDevice.EXTRA_DEVICE);
                if(paired_devices.indexOf(device) != -1){
                    paired_devices.remove(device);
                }
                paired_devices.add(0, device);
                if(adapter != null)adapter.notifyDataSetChanged();
            }else if(BluetoothAdapter.ACTION_DISCOVERY_STARTED.equals(action)){
                setProgressBarIndeterminateVisibility(true);
            }else if(BluetoothAdapter.ACTION_DISCOVERY_FINISHED.equals(action)){
                setProgressBarIndeterminateVisibility(false);
            }
        }
    };
    private static final String TAG = BluetoothDeviceList.class.getSimpleName();

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.device_list_layout);
        listView = (ListView)findViewById(R.id.device_list);
        search_btn = (FloatingActionButton)findViewById(R.id.search_btn);
        mAdapter = BluetoothAdapter.getDefaultAdapter();
        Set<BluetoothDevice> pairedDevices = mAdapter.getBondedDevices();
        if (pairedDevices.size() > 0){
            for (BluetoothDevice device : pairedDevices){
                paired_devices.add(device);
            }
        }
        adapter = new DeviceListAdapter(this, R.layout.device_list_item, paired_devices);
        listView.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> adapterView, View view, int position, long l) {
                mAdapter.cancelDiscovery();
                Intent intent = new Intent();
                intent.putExtra(EXTRA_DEVICE_ADDRESS, adapter.getItemAtPosition(position).getAddress());
                setResult(Activity.RESULT_OK, intent);
                finish();

            }
        });
        listView.setAdapter(adapter);
        search_btn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                mAdapter.startDiscovery();
            }
        });
    }

    @Override
    protected void onStart() {
        super.onStart();
        IntentFilter filter = new IntentFilter(BluetoothDevice.ACTION_FOUND);
        filter.addAction(BluetoothAdapter.ACTION_DISCOVERY_STARTED);
        filter.addAction(BluetoothAdapter.ACTION_DISCOVERY_FINISHED);
        filter.addAction(BluetoothAdapter.ACTION_CONNECTION_STATE_CHANGED);
        registerReceiver(mReceiver, filter);
    }

    @Override
    protected void onDestroy() {
        unregisterReceiver(mReceiver);
        super.onDestroy();
    }

    private class DeviceListAdapter extends ArrayAdapter<BluetoothDevice>{

        private ArrayList<BluetoothDevice> arrayList = new ArrayList<>();


        public DeviceListAdapter(@NonNull Context context, int resource, @NonNull ArrayList<BluetoothDevice> objects) {
            super(context, resource, objects);
            arrayList = objects;
        }

        @SuppressLint("ViewHolder")
        @NonNull
        @Override
        public View getView(int position, @Nullable View convertView, @NonNull ViewGroup parent) {
            View view;
            if(convertView == null) {
                view = ((LayoutInflater) getContext().getSystemService(Context.LAYOUT_INFLATER_SERVICE)
                ).inflate(R.layout.device_list_item, null);
            }else{
                view = convertView;
            }
            if(arrayList.isEmpty()){
                ((TextView) view.findViewById(R.id.item_name)).setText(CANNOT_FOUND);
                ((TextView) view.findViewById(R.id.item_addr)).setText(CANNOT_FOUND);
            }else{
                ((TextView) view.findViewById(R.id.item_name)).setText(arrayList.get(position).getName());
                ((TextView) view.findViewById(R.id.item_addr)).setText(arrayList.get(position).getAddress());
            }
            return view;
        }


        @Override
        public int getCount() {
            return arrayList.size();
        }

        public BluetoothDevice getItemAtPosition(int position){
            return arrayList.get(position);
        }

    }

}
