package com.example.tsixivivo;
import android.app.Application;

import com.example.androidbase.sdkPoolManage;

//import com.example.pro_sdkroot.WorkEnvs;

public class tsixiApplication   extends Application {
    @Override
    public void onCreate() {
        super.onCreate();
        //WorkEnvs.setApplication(this);
        sdkPoolManage.getInstance().setApplication(this);
    }
}
