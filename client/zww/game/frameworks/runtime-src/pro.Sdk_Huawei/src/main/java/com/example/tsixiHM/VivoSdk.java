package com.example.tsixivivo;

//public class VivoSdk {
//}

import android.app.Activity;
import android.app.Application;
import android.content.Context;
import android.content.Intent;
import android.util.Log;

import com.example.androidbase.LogicData.PayParams;
import com.example.androidbase.LogicData.UserExtraData;
import com.example.androidbase.sdkItemBase;
import com.example.androidbase.sdkPoolManage;
import com.vivo.unionsdk.open.OrderResultEventHandler;
import com.vivo.unionsdk.open.OrderResultInfo;
import com.vivo.unionsdk.open.QueryOrderCallback;
import com.vivo.unionsdk.open.VivoAccountCallback;
import com.vivo.unionsdk.open.VivoConstants;
import com.vivo.unionsdk.open.VivoExitCallback;
import com.vivo.unionsdk.open.VivoPayCallback;
import com.vivo.unionsdk.open.VivoPayInfo;
import com.vivo.unionsdk.open.VivoRealNameInfoCallback;
import com.vivo.unionsdk.open.VivoRoleInfo;
import com.vivo.unionsdk.open.VivoUnionSDK;
//import com.example.pro_sdkroot.SdkBaseRef;
//import com.example.pro_sdkroot.WorkEnvs;
//import com.example.pro_sdkroot.utils.PayParams;
//import com.example.pro_sdkroot.utils.UserExtraData;
import com.google.gson.Gson;
//import com.vivo.unionsdk.open.*;

import org.json.JSONException;
import org.json.JSONObject;
import java.io.UnsupportedEncodingException;
import java.net.URLEncoder;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
public class VivoSdk extends sdkItemBase {
    public static Activity activity = null;
    public static Application application = null;
    public static VivoSdk sharePtr = null;

    public static String uid = "";
    private String cpOrderAmount = "";
    static String TAG = "Vivo";
    static Map<String,String> SdkParams = new HashMap<>();

    public String getName(){
        return "VivoSdk";
    }
    public void onCreate(){
        Log.d(TAG,"onCreate");
        sharePtr = this;
    }
    public void onInit(){}
    public void login(String param){
        if(param.equals("VivoSdk")){
            VivoUnionSDK.login(activity);
        }
    }
    public void onLogin(String onJson){
        sdkPoolManage.getInstance().onLogin(this,onJson);
    }
    public void logout(){
        VivoUnionSDK.exit(activity  , new VivoExitCallback() {
            @Override
            public void onExitCancel() {
            }

            @Override
            public void onExitConfirm() {
                onLogout();
            }
        });
    }
    public void onLogout(){
        sdkPoolManage.getInstance().onLogout();
    }
    //public void pay(String sname, PayParams params){}
    public void onPay(String json){}
    public void share(Map<String,String> data){}
    public void onShare(String json){};
    public void submitEvent(String event, String json){}
    public void doSubmitExData(final UserExtraData aEx) {
//        //?????????????????????????????????????????????
        switch (aEx.getDataType()) {
            case UserExtraData.TYPE_LEVEL_UP:{
                VivoUnionSDK.reportRoleInfo(new VivoRoleInfo(
                        aEx.getRoleID(),aEx.getRoleLevel().toString(),
                        aEx.getRoleName(),""+aEx.getServerID(),
                        aEx.getServerName()));
            }break;
            case UserExtraData.TYPE_ENTER_GAME:{
                VivoUnionSDK.reportRoleInfo(new VivoRoleInfo(
                        aEx.getRoleID(),aEx.getRoleLevel().toString(),
                        aEx.getRoleName(),""+aEx.getServerID(),
                        aEx.getServerName()));
            }break;
            case UserExtraData.TYPE_CREATE_ROLE:{
            }break;
            case UserExtraData.TYPE_ON_RECHARGE: {
            }
            break;
        }
    }
    public void otherCallEvent(String name,Map<String,String> data){}
    public void setActivity(Activity act){
        if(activity == null){
            activity = act;
            initSdk();
        }
        activity = act;
    }
    public static boolean setSdkParam(Map<String,String> data){
        TAG = "VivoSdk";
        if(sharePtr == null && data != null && data.size() >0){
            SdkParams.clear();
            for(Map.Entry<String, String> entry : data.entrySet()){
                SdkParams.put(entry.getKey(),entry.getValue());
            }
        }return false;
    }
    public void setApplication(Application app){
        application = app;
    }
    public void initSdk(){
        VivoConstant.APP_ID = SdkParams.get("VivoAPP_ID");
        VivoConstant.CP_ID = SdkParams.get("VivoCP_ID");
        VivoConstant.APP_KEY = SdkParams.get("VivoAPP_KEY");
        VivoConstant.APP_KEY = SdkParams.get("VivoAPP_KEY");
        activity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                VivoUnionSDK.initSdk(activity,VivoConstant.CP_ID,false);
            }
        });
//        com/vivo/unionsdk/utils/MiitHelper
        Log.d("VivoSdkClass", "onCreate: 4");
        Log.d("VivoSdkClass",activity.toString());

        VivoUnionSDK.registerAccountCallback(activity, new VivoAccountCallback() {
            @Override
            public void onVivoAccountLogin(String userName, String openId, String authToken) {
                Map<String,String> data = new HashMap<>();
                uid = openId;
                if(data.containsKey("lianhe") == true ) {
                    data.put("userName", userName);
                    data.put("userid", openId);
                    data.put("token", authToken);
                }else {
                    data.put("userName", userName);
                    data.put("uid", openId);
                    data.put("token", authToken);
                }
                sharePtr.onLogin(new Gson().toJson(data));
            }

            @Override
            public void onVivoAccountLogout(int i) {
                sdkPoolManage.getInstance().onLogout();
            }

            @Override
            public void onVivoAccountLoginCancel() {
                //share().doLogOut();
                sdkPoolManage.getInstance().onLogout();
            }
        });
        VivoUnionSDK.registerOrderResultEventHandler(new OrderResultEventHandler() {
            @Override
            public void process(OrderResultInfo orderResultInfo) {
                //Log.i(TAG, "process: "+orderResultInfo.toString());
            }
        });

        Log.d("VivoSdkClass", "onCreate: 5");
    }
    static public boolean getRealNameInfo(){

//        if(WorkEnvs.containsLuaBackKey("RealNameBack") == false)
//            return false;
        VivoUnionSDK.getRealNameInfo( activity, new VivoRealNameInfoCallback() {
            @Override
            public void onGetRealNameInfoSucc(boolean isRealName, int age) {
                Map<String,String> data = new HashMap<>();
                data.put("SdkBack","true");
                data.put("IsOk",""+isRealName);
                data.put("age",""+age);
                //WorkEnvs.callLuaEvent("RealNameBack",new Gson().toJson(data).toString());
            }

            @Override
            public void onGetRealNameInfoFailed() {
                Map<String,String> data = new HashMap<>();
                data.put("SdkBack","false");

                //WorkEnvs.callLuaEvent("RealNameBack",new Gson().toJson(data).toString());
            }
        });
        return true;
    }

    private VivoPayCallback mVivoPayCallback = new VivoPayCallback() {
        // ???????????????????????????????????????????????????????????????????????????????????????????????????????????????
        @Override
        public void onVivoPayResult(int i, OrderResultInfo orderResultInfo) {
            Log.i(TAG, "onVivoPayResult: " + orderResultInfo.getTransNo());
            if (i == VivoConstants.PAYMENT_RESULT_CODE_SUCCESS) {
                Log.d("vivo Sdk", "????????????");
                //!!!! ????????????????????????????????????????????? !!!
                //?????????????????????????????????vivo???
                VivoUnionHelper.sendCompleteOrderNotification(orderResultInfo);
            } else if (i == VivoConstants.PAYMENT_RESULT_CODE_CANCEL) {
                Log.d("vivo Sdk", "????????????");
            } else if (i == VivoConstants.PAYMENT_RESULT_CODE_UNKNOWN) {
                Log.d("vivo Sdk","??????????????????????????????");
                VivoUnionHelper.queryOrderResult(orderResultInfo.getCpOrderNumber(), orderResultInfo.getTransNo(),
                        orderResultInfo.getProductPrice(), new QueryOrderCallback() {
                            @Override
                            public void onResult(int i, OrderResultInfo orderResultInfo) {
                                switch (i) {
                                    case OrderResultInfo.STATUS_PAY_SUCCESS://???????????????????????????
                                        //TODO ???????????????
                                        //!!!! ????????????????????????????????????????????? !!!
                                        //?????????????????????????????????vivo???
                                        VivoUnionHelper.sendCompleteOrderNotification(orderResultInfo);
                                        break;
                                    case OrderResultInfo.STATUS_PAY_UNTREATED://????????????????????????
                                        break;
                                }
                            }
                        });
            } else {
                Log.d("vivo Sdk", "????????????");
            }
        }

    };

    public static String getSignature(OrderBean orderBean) {
        HashMap<String, String> params = new HashMap<>();
        params.put(VivoConstant.APP_ID_PARAM,VivoConstant.APP_ID);
        params.put(VivoConstant.CP_ORDER_NUMBER, orderBean.getCpOrderNumber());
        params.put(VivoConstant.EXT_INFO, orderBean.getExtInfo());
        params.put(VivoConstant.NOTIFY_URL, orderBean.getNotifyUrl());
        params.put(VivoConstant.ORDER_AMOUNT, orderBean.getOrderAmount());
        params.put(VivoConstant.PRODUCT_DESC, orderBean.getProductDesc());
        params.put(VivoConstant.PRODUCT_NAME, orderBean.getProductName());

        params.put(VivoConstant.BALANCE, orderBean.getRoleInfoBean().getBalance());
        params.put(VivoConstant.VIP, orderBean.getRoleInfoBean().getVip());
        params.put(VivoConstant.LEVEL, orderBean.getRoleInfoBean().getLevel());
        params.put(VivoConstant.PARTY, orderBean.getRoleInfoBean().getParty());
        params.put(VivoConstant.ROLE_ID, orderBean.getRoleInfoBean().getRoleId());
        params.put(VivoConstant.ROLE_NAME, orderBean.getRoleInfoBean().getRoleName());
        params.put(VivoConstant.SERVER_NAME, orderBean.getRoleInfoBean().getServerName());
        return VivoSignUtils.getVivoSign(params,VivoConstant.APP_KEY);
    }
    public void pay(String sname,PayParams aParams) {
        //??????1???????????????????????????
        try{
            RoleInfoBean rib = new RoleInfoBean("","","",
                    "",""+aParams.getRoleId(),aParams.getRoleName(),
                    aParams.getServerName());
            String str = new Gson().toJson(rib).toString();
            Log.d("doPay", str);
            String exData = aParams.getExtension();
            String url = "";
            try {
                JSONObject js = new JSONObject(exData);
                Object obj = "";
                //url = WorkEnvs.CheckGetParams(js, "notifyUrl", obj).toString();
            }catch (JSONException je){

            }finally {
                Float Price = aParams.getPrice();
                long price = Price.longValue() * 100;
                cpOrderAmount = price+"";
                OrderBean orderBean = new OrderBean(

                        aParams.getOrderID(),"",
                        url,cpOrderAmount,aParams.getProductName(),
                        aParams.getProductDesc(),rib);
                String signature = getSignature(orderBean);
                //??????2?????????VivoPayInfo
                VivoPayInfo vivoPayInfo = new VivoPayInfo.Builder()
                        //??????????????????
                        .setAppId(VivoConstant.APP_ID)
                        .setCpOrderNo(orderBean.getCpOrderNumber())
                        .setExtInfo(orderBean.getExtInfo())
                        .setNotifyUrl(orderBean.getNotifyUrl())
                        .setOrderAmount(orderBean.getOrderAmount())
                        .setProductDesc(orderBean.getProductDesc())
                        .setProductName(orderBean.getProductName())
                        //????????????
                        .setBalance(orderBean.getRoleInfoBean().getBalance())
                        .setVipLevel(orderBean.getRoleInfoBean().getVip())
                        .setRoleLevel(orderBean.getRoleInfoBean().getLevel())
                        .setParty(orderBean.getRoleInfoBean().getParty())
                        .setRoleId(orderBean.getRoleInfoBean().getRoleId())
                        .setRoleName(orderBean.getRoleInfoBean().getRoleName())
                        .setServerName(orderBean.getRoleInfoBean().getServerName())
                        //???????????????????????????
                        .setVivoSignature(signature)
                        //??????vivo?????????uid???????????????""
                        .setExtUid(uid)
                        .build();
                VivoUnionSDK.payV2(activity, vivoPayInfo, mVivoPayCallback);
            }

        }
        catch (Exception ex){
            ex.printStackTrace();
        }
    }
}
