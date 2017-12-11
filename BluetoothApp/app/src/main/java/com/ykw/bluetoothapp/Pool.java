package com.ykw.bluetoothapp;

import android.util.Log;

import java.util.Queue;
import java.util.concurrent.ConcurrentLinkedDeque;
import java.util.concurrent.ConcurrentLinkedQueue;

/**
 * Created by dbsrh on 2017-12-02.
 */

public class Pool<T> {
    private ConcurrentLinkedQueue<T> pool;

    private final int pool_size;

    public Pool(int size){
        pool = new ConcurrentLinkedQueue<>();
        pool_size = size;
    }

    private synchronized boolean isFulled(){
        return (pool.size() >= pool_size);
    }

    private boolean isEmpty(){
        return pool.isEmpty();
    }

    public void add(T obj) {
        pool.add(obj);
    }

    public synchronized boolean delete(T obj){
        return pool.remove(obj);
    }

    public synchronized T get(){
        return pool.poll();
    }

    public int getPool_size() {
        return pool_size;
    }
}
