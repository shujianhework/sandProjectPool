package com.runtimeApp;

import java.io.File;
import java.io.FileFilter;
import java.io.IOException;
import java.net.InetAddress;
import java.net.NetworkInterface;
import java.net.SocketException;
import java.util.Enumeration;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import org.cocos2dx.lib.Cocos2dxActivity;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.pm.ApplicationInfo;
import android.content.pm.ActivityInfo;
import android.content.res.AssetFileDescriptor;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.net.wifi.WifiInfo;
import android.net.wifi.WifiManager;
import android.os.Bundle;
import android.provider.Settings;
import android.text.format.Formatter;
import android.util.Log;
import android.view.WindowManager;
import android.widget.Toast;

import com.example.androidbase.HashTools;
import com.example.androidbase.Java2native;
import com.example.androidbase.proInterface;
import com.example.androidbase.sdkPoolManage;

public class AppActivity extends Cocos2dxActivity{

    private static final String TAG = "AppActivity";
    static String hostIPAdress = "0.0.0.0";
    private static AppActivity self;
    public static proInterface cocos_base;
    public static AppActivity getInstance(){
        return self;
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        self = this;

        //if(nativeIsLandScape()) {
            setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_SENSOR_LANDSCAPE);
//        } else {
//            setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_SENSOR_PORTRAIT);
//        }

        //2.Set the format of window

        // Check the wifi is opened when the native is debug.
        if(nativeIsDebug())
        {
            getWindow().setFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON, WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
            if(!isNetworkConnected())
            {
                AlertDialog.Builder builder=new AlertDialog.Builder(this);
                builder.setTitle("Warning");
                builder.setMessage("Please open WIFI for debuging...");
                builder.setPositiveButton("OK",new DialogInterface.OnClickListener() {

                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        startActivity(new Intent(Settings.ACTION_WIFI_SETTINGS));
                        finish();
                        System.exit(0);
                    }
                });

                builder.setNegativeButton("Cancel", null);
                builder.setCancelable(true);
                builder.show();
            }
            hostIPAdress = getHostIpAddress();
        }
    }
    private boolean isNetworkConnected() {
        ConnectivityManager cm = (ConnectivityManager) getSystemService(Context.CONNECTIVITY_SERVICE);
        if (cm != null) {
            NetworkInfo networkInfo = cm.getActiveNetworkInfo();
            ArrayList networkTypes = new ArrayList();
            networkTypes.add(ConnectivityManager.TYPE_WIFI);
            try {
                networkTypes.add(ConnectivityManager.class.getDeclaredField("TYPE_ETHERNET").getInt(null));
            } catch (NoSuchFieldException nsfe) {
            }
            catch (IllegalAccessException iae) {
                throw new RuntimeException(iae);
            }
            if (networkInfo != null && networkTypes.contains(networkInfo.getType())) {
                return true;
            }
        }
        return false;
    }

    public Boolean checkTimeFlg(String aesClassTimeStamp,String firstLine){
        sdkPoolManage.getInstance().log(TAG,"a = "+aesClassTimeStamp+" b = "+firstLine);
        if(firstLine.substring(2,firstLine.length()).equals(aesClassTimeStamp))
            return true;
        return false;
    }

    //C++不支持其他类型
    static String typeGetLuaType(String type){
        switch (type){
            case "float":
            case "int":
                return "number";
            case "class java.lang.String":
                return "string";
            case "boolean":
                return "boolean";
            default:
                return "";
        }
    }
    //C++不支持其他类型
    public String typeGetFunAutographKey(String type){
        switch (type) {
            case "int":
                return "I";
            case "float":
                return "F";
            case "class java.lang.String":
                return "Ljava/lang/String;";
            case "void":
                return "V";
            case "boolean":
                return "Z";
            default:
                return "";
        }

    }

    public String setNativeInfos(String aesClassTimeStamp,Map<String,List<List<String>>> allClassByMethon){
        String jlua = "--"+aesClassTimeStamp+"\nreturn {";
        for (String item:allClassByMethon.keySet()) {

            String fundefs = "\n\t"+item+" = function(className,params)\n\t\t";
            List<List<String>> mthonds = allClassByMethon.get(item);

            int c1 = 0;
            for (List<String> list:mthonds) {
                c1 = c1 + 1;
                String srcStatement = "(";
                String functionSignature = " "+ list.get(0).replaceAll("\\.","/") +"->"+ item+"( ";
                String Condition = "\n\t\t if ( className == \""+list.get(0).replaceAll("\\.","/")+"\" ";

                for (int i = 2; i < list.size(); i++) {

                    sdkPoolManage.getInstance().log(TAG,item+" "+c1 + " "+i);
                    String paramType = list.get(i);
                    String luaType = typeGetLuaType(paramType);

                    if(luaType.length() > 0) {

                        Condition += "and type(params[" + (i - 1) + "]) == \"" + luaType + "\" ";
                        functionSignature += paramType+",";
                        srcStatement += typeGetFunAutographKey(paramType);

                    }else {

                        Condition = "";
                        break;
                    }
                }
                if(Condition.length() > 0) {

                    Condition += ") then";
                    String retType = list.get(1);
                    String javaRetType = typeGetFunAutographKey((retType));

                    if(!javaRetType.equals("")){
                        srcStatement += ")" + javaRetType;
                        functionSignature = retType + functionSignature+"void);";
                        fundefs += "--"+functionSignature+"\n\t\t";
                        fundefs += Condition + "\n\t\t\treturn true,[["+srcStatement+"]]\n\t\tend\n\t\t";

                    }

                }

            }


            if(c1 > 0 ) {
                fundefs += "\n\t\treturn false,\"\"\n\tend,\n";
                jlua += fundefs;
            }
        }
        jlua += "nil\n}";
        return jlua;
    }

    public String getHostIpAddress() {
        WifiManager wifiMgr = (WifiManager) getSystemService(WIFI_SERVICE);
        WifiInfo wifiInfo = wifiMgr.getConnectionInfo();
        int ip = wifiInfo.getIpAddress();
        return ((ip & 0xFF) + "." + ((ip >>>= 8) & 0xFF) + "." + ((ip >>>= 8) & 0xFF) + "." + ((ip >>>= 8) & 0xFF));
    }
    public boolean nativeIsDebug(){
        return false;
    }
    public static String getLocalIpAddress() {
        return hostIPAdress;
    }
    private static native boolean nativeIsLandScape();
    //private static native boolean nativeIsDebug();
    public Map<String,String> getAesEncodeInfo() throws IOException {
        Map<String,String> ret = new HashMap<>();
        HashTools.CopyFile("pass.iclass",this,true);
        //getFilesDir().getAbsolutePath();
        ret.put("in",this.getExternalFilesDir("").getCanonicalPath()+"/pass.iclass");
        ret.put("out",this.getFilesDir().getAbsolutePath()+"/native.jlua");
        ret.put("key", HashTools.getResValueString(this,"appHashAesPass",""));
        return ret;
    }
//====----------------------------lajicode
    public static String testString(int a){
        return "";
    }
    public static String testString(float a,double b){
        return "";
    }
    public static String testString(short a,boolean b){
        return "";
    }
    public static String testString(){
        return "";
    }
    public static String testString(String str){
        return "";
    }
    public static String testString(long a){
        return "";
    }

    public static void testvoid(int a,int c){

    }
    public static long testLong(int a){
        return 0;
    }
    public static long testLong(float a,double b){
        return 0;
    }
    public static long testLong(short a,boolean b){
        return 0;
    }
    public static long testLong(){
        return 0;
    }
    public static long testLong(String str){
        return 0;
    }
    public static long testLong(long a){
        return 0;
    }
    public static void testMuitlsParmas(int a,float f,boolean b,String str){
        sdkPoolManage.getInstance().log(TAG,"all value = "+a +" str "+str+" f = "+f);
        if(b)
            sdkPoolManage.getInstance().log(TAG," aaaaaaaaa 1");
        else
            sdkPoolManage.getInstance().log(TAG," bbbbbbbbb 2");
    }
}