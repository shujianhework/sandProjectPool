package com.example.centerapp.Components;

import com.example.centerapp.Tools.MessageNotifyData;

import java.security.MessageDigest;

public interface ComponentBase {

    public String getName();
    public void open();
    public void close();
    public void onMessageHandle(MessageNotifyData data);
}
