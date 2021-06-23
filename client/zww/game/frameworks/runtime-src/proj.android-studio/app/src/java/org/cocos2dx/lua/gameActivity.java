/****************************************************************************
Copyright (c) 2015 Chukong Technologies Inc.
 
http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package org.cocos2dx.lua;

import java.net.InetAddress;
import java.net.NetworkInterface;
import java.net.SocketException;
import java.util.Enumeration;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import org.cocos2dx.lib.Cocos2dxActivity;

import android.app.AlertDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.pm.ApplicationInfo;
import android.content.pm.ActivityInfo;
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
import com.example.androidbase.sdkPoolManage;
import com.runtimeApp.AppActivity;


public class gameActivity extends AppActivity {
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        //sdkPoolManage.getInstance().setActivity(this);
        Java2native.getInstance().setActivity(this);
    }

    @Override
    public boolean nativeIsDebug() {
        return false;
    }

    @Override
    protected void onResume() {
        super.onResume();
        sdkPoolManage.getInstance().androidActHandle(this,"onResume");
    }

    @Override
    protected void onPause() {
        super.onPause();
        sdkPoolManage.getInstance().androidActHandle(this,"onPause");
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        sdkPoolManage.getInstance().androidActHandle(this,"onDestroy");
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        sdkPoolManage.getInstance().androidActHandle(this,"onActivityResult",requestCode,resultCode,data);
    }
//    @Override
//    public Map<String,String> getAesEncodeInfo(){
//        Map<String,String> ret = super.getAesEncodeInfo();
//        return ret;
//    }
}
