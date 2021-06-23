package com.androidBase;
import android.util.Log;

import com.example.androidbase.LogicData.sdkPoolInitInsertProxy;
//import com.example.tsixivivo.VivoSdk;
import com.example.quick.quickSdk;
import com.runtimeApp.cocosBase;

import java.util.HashMap;
import java.util.Map;

public class appBridging {
    static public void loadVivo(){
        Map<String,String> data = new HashMap<>();
        data.put("VivoAPP_ID","103873325");
        data.put("VivoCP_ID","4f1336937010ec72e481");
        data.put("VivoAPP_KEY","83948a086029874d3d0680497aa00a25");
        //VivoSdk.setSdkParam(data);
    }
    static public void loadQuick(){
        Map<String,String> data = new HashMap<>();
        data.put("isLandscape","true");
        data.put("product_code","92103705944253602436306168796256");
        data.put("product_key","56684743");
        quickSdk.setSdkParam(data);
    }
    public static void init(sdkPoolInitInsertProxy spiip){
        Log.d("aaa","111");
        //loadVivo();
//        VivoSdk sdk = new VivoSdk();
//        spiip.insert(sdk);
        quickSdk quicksdk = new quickSdk();
        spiip.insert(quicksdk);
    }
    static public void init(appBridging a, sdkPoolInitInsertProxy spiip){
        Log.d("aaa","222");
        a.init(spiip);
    }
    public Class getProHandleProjectObject(){
        return cocosBase.class;
    }
}
