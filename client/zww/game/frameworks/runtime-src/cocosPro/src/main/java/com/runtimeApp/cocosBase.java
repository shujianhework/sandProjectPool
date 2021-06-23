package com.runtimeApp;
import android.app.Activity;
import android.nfc.Tag;
import android.os.strictmode.NonSdkApiUsedViolation;
import android.util.Log;
import com.example.androidbase.LogicData.PayParams;
import com.example.androidbase.proInterface;
import com.example.androidbase.sdkPoolManage;

import org.cocos2dx.lib.Cocos2dxLuaJavaBridge;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
public class cocosBase implements proInterface {
    final  public static String TAG = "ddt";
    static public Map<String,Integer> luaFuns = new HashMap<String, Integer>();

    public cocosBase() {
        super();
        AppActivity.cocos_base = this;
    }

    public void callLuaBack(final String name,final String value){

        log(name+"("+value+") 1");
        if(luaFuns.containsKey(name)){

            AppActivity.getInstance().runOnGLThread(new Runnable() {
                @Override
                public void run() {
                    log(name+"("+value+") 2");
                    Cocos2dxLuaJavaBridge.callLuaFunctionWithString(luaFuns.get(name),value);
                    log(name+"("+value+") 3");
                }
            });
            log(name+"("+value+") 4");
        }
        log(name+"("+value+") 5");

    }

    public void log(Object str){
        sdkPoolManage.getInstance().log(TAG,str);
    }

    @Override
    public void login(String param) {
        log("login");
        sdkPoolManage.getInstance().login(param);
    }

    @Override
    public void onLogin(String onJson) {
        callLuaBack("login",onJson);
    }

    @Override
    public void logout() {
        Log.d(TAG,"logout");
        sdkPoolManage.getInstance().logout();
    }

    @Override
    public void onLogout() {
        Log.d(TAG,"onLogOut");
        callLuaBack("logout","");
    }

    @Override
    public void pay(PayParams param) {
        Log.d(TAG,"pay");
        sdkPoolManage.getInstance().pay(param);
    }

    @Override
    public void onPay(String json) {
        Log.d(TAG,"onPay");
        callLuaBack("pay",json);
    }

    @Override
    public void share(Map<String, String> data) {
        Log.d(TAG,"share");
        sdkPoolManage.getInstance().share(data);
    }

    @Override
    public void onShare(String json) {
        callLuaBack("share",json);
    }

    @Override
    public void submitEvent(String event, String json) {
        Log.d(TAG,"submitEvent name = "+event);
        sdkPoolManage.getInstance().submitEvent(event,json);
    }

    @Override
    public void submitRoleInfos(String json) {
        Log.d(TAG,"submitRoleInfos name = ");
        sdkPoolManage.getInstance().submitRoleInfos(null);
    }

    @Override
    public void otherCallEvent(String name, Map<String, String> data) {
        sdkPoolManage.getInstance().otherCallEvent(name,data);
    }

    static public void login(String name,int fun){
        AppActivity.cocos_base.login(name);
    }

    static public void setOtherBack(String name,int fun){

        if(luaFuns.containsKey(name)){
            Integer oldid = luaFuns.get(name);
            Cocos2dxLuaJavaBridge.releaseLuaFunction(oldid);
        }

        if( name != null && name.length() > 0){
            Cocos2dxLuaJavaBridge.retainLuaFunction(fun);
            luaFuns.put(name,fun);
        }

    }

    static public void swtich(int fun){

        AppActivity.cocos_base.logout();

    }

    static public void pay(PayParams param,int fun){

        AppActivity.cocos_base.pay(param);

    }

    static public void share(Map<String, String> data,int fun){

        AppActivity.cocos_base.share(data);

    }

    static public void luaSubmitEvent(String event, String json){

        AppActivity.cocos_base.submitEvent(event,json);

    }

    static public void luaSubmitRoleInfos(String json){

        AppActivity.cocos_base.submitRoleInfos(json);

    }

    static public void clearNativeLog(int fun){
        sdkPoolManage.clearNativeLog();;
    }

    static public void getLogsLists(int fun){

        if(luaFuns.containsKey("getLogsLists") == false)
            return;

        final cocosBase base = (cocosBase) AppActivity.cocos_base;
        base.log("getLogsLists 1");
        final  List<String> list = sdkPoolManage.getNativeLogs();

        AppActivity.getInstance().runOnGLThread(new Runnable() {
            @Override
            public void run() {

                base.log("getLogsLists 2");
                Integer luaFunid = luaFuns.get("getLogsLists");
                for (String item:list) {
                    Cocos2dxLuaJavaBridge.callLuaFunctionWithString(luaFunid,item);
                }
                base.log("getLogsLists 3");

            }
        });
    }
}
