package com.example.androidbase;

import android.app.Activity;
import android.app.Application;

import com.example.androidbase.LogicData.PayParams;
import com.example.androidbase.LogicData.UserExtraData;

import java.util.Map;

public class sdkItemBase {
    public String getName(){
        return "sdkItemBase";
    }
    public void onCreate(){}
    public void onInit(){}
    public void login(String param){}
    public void onLogin(String onJson){}
    public void logout(){}
    public void onLogout(){}
    public void pay(String sname, PayParams params){}
    public void onPay(String json){}
    public void share(Map<String,String> data){}
    public void onShare(String json){};
    public void submitRoleInfos(final UserExtraData data){}
    public void submitEvent(String event, String json){}
    public void otherCallEvent(String name,Map<String,String> data){}
    public void setActivity(Activity act){}
    public void setApplication(Application app){}
}
