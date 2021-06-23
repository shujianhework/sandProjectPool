package com.example.androidbase;

import android.app.Activity;
import android.app.Application;
import android.content.Context;
import android.nfc.Tag;
import android.os.Build;
import android.util.Log;

import androidx.annotation.RequiresApi;

import java.io.IOException;
import java.io.PrintWriter;
import java.io.StringWriter;
import java.io.Writer;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.lang.reflect.Modifier;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import com.example.androidbase.LogicData.*;
public class sdkPoolManage {
    Map<String,sdkItemBase> sdkPools = new HashMap<>();
    static private sdkPoolManage instan = null;
    static  String sdkDefineName = "";
    static String curLoginSdkName = "";
    static final String TAG = "sdkPool";
    static final Boolean debugLog = true;
    static proInterface proGroup = null;
    static private List<String> nativeLogs = new ArrayList<String>();

    public static Object newObj(String className, Object... args) throws ClassNotFoundException, NoSuchMethodException, IllegalAccessException, InvocationTargetException, InstantiationException {
        Class[] classes = new Class[args.length];
        for (int i = 0; i < classes.length; i++) {
            classes[i] = args[i].getClass();
        }
        Object obj = null;
        obj = Class.forName(className).getConstructor(classes).newInstance(args);
        return obj;
    }
    private void init(){
        //查找一个类名调用他的成员函数有并传入参数
        sdkDefineName = "";
        sdkPoolInitInsertProxy spiip = new sdkPoolInitInsertProxy() {
            @Override
            public boolean insert(sdkItemBase sdk) {
                String name = sdk.getName();
                if(sdkPools.containsKey(name)){
                    return false;
                }
                //Object obj = Class.forName("com.androidBase.appBridging").getConstructor(classes).newInstance(args);
                sdkPools.put(name,sdk);
                return true;
            }
        };
        try{
            Object obj = newObj("com.androidBase.appBridging");
            Method metini = obj.getClass().getMethod("init",sdkPoolInitInsertProxy.class);
            metini.invoke(obj,spiip);
            Method metppo = obj.getClass().getMethod("getProHandleProjectObject");
            Class cls = (Class)metppo.invoke(obj);
            proGroup = (proInterface)cls.newInstance();

        }catch (Exception ex){
            ex.printStackTrace();
            Log.e(TAG,"check sdk ini or sdk class or Class:com.androidBase.appBridging");
        }
        if(sdkPools.size() > 1 && sdkPools.containsKey("sdkItemBase")){
            sdkPools.remove("sdkItemBase");
        }
        assert (sdkPools.size()>0);
        if(sdkPools.size() == 1) {
            for (String item : sdkPools.keySet()) {
                sdkDefineName = item;
            }
        }
    }
    public static sdkPoolManage getInstance(){
//        getAesEncodeInfo
        if(instan == null){
            instan = new sdkPoolManage();
            instan.init();
            Java2native.getInstance();
        }
        return instan;
    }
    public void login(String param){
        Log.d(TAG,"login param + "+param);
        for (String key:sdkPools.keySet()) {
            sdkPools.get(key).login(param);
        }
    }
    public void onLogin(sdkItemBase item, String onJson){
        String name = item.getName();
        assert(name != null && name.isEmpty() == false);
        Log.d(TAG,"onLogin:"+name+":"+onJson);
        if(item.equals(sdkPools.get(name))) {
            if(curLoginSdkName.isEmpty()) {
                curLoginSdkName = name;
                proGroup.onLogin(onJson);
            }else{
                Log.d(TAG,"other Sdk Login Handler,ignore current Login Event !!!!!!!!!!!!!!!");
            }
        }else{
            Log.e(TAG,"Invalid callback sdk "+name);
        }
    }
    public void logout(){
        if(curLoginSdkName.isEmpty() == false){
            return;
        }
        Log.d(TAG,"logout");
        sdkPools.get(curLoginSdkName).logout();
    }
    public void onLogout(){
        Log.d(TAG,"onLogout");
        proGroup.onLogout();
    }
    public void pay(PayParams param){
        Log.d(TAG,"pay");
        for (String str:sdkPools.keySet()) {
            sdkPools.get(str).pay("",param);
        }
    }
    public void onPay(sdkItemBase sdk,String json){
        Log.d(TAG,"onPay");
        String name = sdk.getName();
        if(sdkPools.get(name).equals(sdk) == false){
            Log.d(TAG,"Invalid callback sdk on Pay " + name);
        }
        proGroup.onPay(json);
    }
    public void share(Map<String,String> data){

    }
    public void onShare(String json){};
    public void submitEvent(String name, String json){
        Log.d(TAG,"submitEvent");
        for (String item:sdkPools.keySet()) {
            sdkPools.get(item).submitEvent(name,json);
        }
    }
    public void submitRoleInfos(final UserExtraData data){
        Log.d(TAG,"submitRoleInfos");
        for (String item:sdkPools.keySet()) {
            sdkPools.get(item).submitRoleInfos(data);
        }
    }
    public void otherCallEvent(String name,Map<String,String> data){}
    public void androidActHandle(Activity context,String funname,Object... args){
        Class[] classes = new Class[args.length];
        for (int i = 0; i < classes.length; i++) {
            classes[i] = args[i].getClass();
        }
        for (String item:sdkPools.keySet()) {
            Object obj = sdkPools.get(item);
            try {
                Method method = obj.getClass().getMethod("act_" + funname, classes);
                int modifier = method.getModifiers();
                if(Modifier.isStatic(modifier)){
                    method.invoke(args);
                }else
                    method.invoke(obj,args);
            }catch (Exception ex){
                ex.printStackTrace();
            }
        }
    }
    public void androidAppHandle(Activity context,String funname,Object... args){
        Class[] classes = new Class[args.length];
        for (int i = 0; i < classes.length; i++) {
            classes[i] = args[i].getClass();
        }
        for (String item:sdkPools.keySet()) {
            Object obj = sdkPools.get(item);
            try {
                Method method = obj.getClass().getMethod("app_" + funname, classes);
                int modifier = method.getModifiers();
                if(Modifier.isStatic(modifier)){
                    method.invoke(args);
                }else
                    method.invoke(obj,args);
            }catch (Exception ex){
                ex.printStackTrace();
            }
        }
    }
    public void setActivity(Activity act){
        Log.d(TAG,"setActivity");
        for (String key:sdkPools.keySet()) {
            sdkPools.get(key).setActivity(act);
        }
    }
    public void setApplication(Application app){
        Log.d(TAG,"setApplication");
        for (String key:sdkPools.keySet()) {
            sdkPools.get(key).setApplication(app);
        }
    }

    public void log(String tag,Object value){

        if(value == null)
            Log.d(tag,null);
        else
            Log.d(tag,""+value);

        if(debugLog){

            String str = tag+":";
            if(value != null)
                str = str + value;
            if(nativeLogs.size() > 1024){
                nativeLogs.remove(0);
            }
            nativeLogs.add(str);
        }
    }

    static public void clearNativeLog(){

        nativeLogs.clear();

    }

    static public List<String> getNativeLogs(){

        if(debugLog == false)
            nativeLogs.clear();
        return nativeLogs;

    }

    public void printStackTrace(String tag, Exception ex){

        Writer writer = null;
        PrintWriter printWriter = null;

        try {
            writer = new StringWriter();
            printWriter = new PrintWriter(writer);
            ex.printStackTrace(printWriter);
            String str = writer.toString();
            log(tag,str);

        }catch (Exception ex1){

            log(tag,"printStackTrace 2 string err");
            ex1.printStackTrace();

        }
        finally {

            try {
                if (writer != null)
                    writer.close();
                if (printWriter != null)
                    printWriter.close();
            } catch (IOException e1) { }

        }

    }
}
