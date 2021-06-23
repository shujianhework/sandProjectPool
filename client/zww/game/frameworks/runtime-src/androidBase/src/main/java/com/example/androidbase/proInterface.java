package com.example.androidbase;

import android.app.Activity;
import android.app.Application;

import com.example.androidbase.LogicData.PayParams;

import java.util.Map;

public interface proInterface {
    public void login(String param);
    public void onLogin(String onJson);
    public void logout();
    public void onLogout();
    public void pay(PayParams params);
    public void onPay(String json);
    public void share(Map<String,String> data);
    public void onShare(String json);
    public void submitEvent(String event, String data);
    public void submitRoleInfos(String json);
    public void otherCallEvent(String name,Map<String,String> data);
}
