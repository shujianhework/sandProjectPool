package com.example.quick;

//public class VivoSdk {
//}

import android.Manifest;
import android.app.Activity;
import android.app.Application;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.text.style.IconMarginSpan;
import android.util.Log;

import com.example.androidbase.LogicData.PayParams;
import com.example.androidbase.LogicData.UserExtraData;
import com.example.androidbase.sdkItemBase;
import com.example.androidbase.sdkPoolManage;
import com.google.gson.Gson;
import com.quicksdk.QuickSDK;
import com.quicksdk.entity.GameRoleInfo;
import com.quicksdk.entity.OrderInfo;
import com.quicksdk.entity.UserInfo;
import com.quicksdk.notifier.ExitNotifier;
import com.quicksdk.notifier.InitNotifier;
import com.quicksdk.notifier.LoginNotifier;
import com.quicksdk.notifier.LogoutNotifier;
import com.quicksdk.notifier.PayNotifier;
import com.quicksdk.notifier.SwitchAccountNotifier;

import org.json.JSONException;
import org.json.JSONObject;

import java.util.HashMap;
import java.util.Map;
public class quickSdk extends sdkItemBase {
    public static Activity activity = null;
    public static Application application = null;
    public static quickSdk sharePtr = null;

    public static String uid = "";
    private String cpOrderAmount = "";
    static String TAG = "Quick";
    static Map<String,String> SdkParams = new HashMap<>();

    public String getName(){
        return "quickSdk";
    }
    public void onCreate(){
        Log.d(TAG,"onCreate");
        sharePtr = this;
    }
    public void onInit(){}
    public void login(String param){
        if(param.equals("QuickSdk")){
            activity.runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    com.quicksdk.User.getInstance().login(activity);
                }
            });
        }
    }
    public void onLogin(String onJson){
        sdkPoolManage.getInstance().onLogin(this,onJson);
    }
    public void logout(){
        activity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                com.quicksdk.User.getInstance().logout(activity);
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
    private void initQkNotifiers() {
        QuickSDK.getInstance()
                // 1.设置初始化通知(必接)
                .setInitNotifier(new InitNotifier() {

                    @Override
                    public void onSuccess() {

                    }

                    @Override
                    public void onFailed(String message, String trace) {
                        //infoTv.setText("初始化失败:" + message);
                    }
                })
                // 2.设置登录通知(必接)
                .setLoginNotifier(new LoginNotifier() {

                    @Override
                    public void onSuccess(UserInfo userInfo) {
                        if (userInfo != null) {
                            // 登录成功之后，进入游戏时，需要向渠道提交用户信息
                            Map<String,String> map = new HashMap<>();
                            map.put("UserID",userInfo.getUID());
                            map.put("UserName",userInfo.getUserName());
                            map.put("Token",userInfo.getToken());
                            onLogin(new Gson().toJson(map));
                        }
                    }

                    @Override
                    public void onCancel() {
                        onLogin("");
                    }

                    @Override
                    public void onFailed(final String message, String trace) {
                        //infoTv.setText("登陆失败:" + message);
                        onLogin("");
                    }

                })
                // 3.设置注销通知(必接)
                .setLogoutNotifier(new LogoutNotifier() {

                    @Override
                    public void onSuccess() {
                        onLogout();
                    }

                    @Override
                    public void onFailed(String message, String trace) {

                    }
                })
                // 4.设置切换账号通知(必接)
                .setSwitchAccountNotifier(new SwitchAccountNotifier() {

                    @Override
                    public void onSuccess(UserInfo userInfo) {
                        if (userInfo != null) {
//                            infoTv.setText("切换账号成功" + "\n\r" + "UserID:  " + userInfo.getUID() + "\n\r" + "UserName:  " + userInfo.getUserName() + "\n\r"
//                                    + "Token:  " + userInfo.getToken());
                        }
                    }

                    @Override
                    public void onFailed(String message, String trace) {

                    }

                    @Override
                    public void onCancel() {

                    }
                })
                // 5.设置支付通知(必接)
                .setPayNotifier(new PayNotifier() {

                    @Override
                    public void onSuccess(String sdkOrderID, String cpOrderID, String extrasParams) {
                        //infoTv.setText("支付成功，sdkOrderID:" + sdkOrderID + ",cpOrderID:" + cpOrderID);
                        Map<String,String> map = new HashMap<>();
                        map.put("sdkOrderID",sdkOrderID);
                        map.put("cpOrderID",cpOrderID);
                        onPay(new Gson().toJson(map));
                    }

                    @Override
                    public void onCancel(String cpOrderID) {
                        onPay("");
                    }

                    @Override
                    public void onFailed(String cpOrderID, String message, String trace) {
                        onPay("");
                    }
                })
                // 6.设置退出通知(必接)
                .setExitNotifier(new ExitNotifier() {

                    @Override
                    public void onSuccess() {
                        // 进行游戏本身的退出操作，下面的finish()只是示例
                        activity.finish();
                    }

                    @Override
                    public void onFailed(String message, String trace) {
                    }
                });
    }
    public void doSubmitExData(final UserExtraData aEx) {
        if(aEx.getDataType() >= 0 && aEx.getDataType() <= 3){
            GameRoleInfo roleInfo = new GameRoleInfo();
            roleInfo.setServerID(""+aEx.getServerID());// 服务器ID
            roleInfo.setServerName(aEx.getServerName());// 服务器名称
            roleInfo.setGameRoleName(aEx.getRoleName());// 角色名称
            roleInfo.setGameRoleID(aEx.getRoleID());// 角色ID
            roleInfo.setGameUserLevel(aEx.getRoleLevel());// 等级
            roleInfo.setVipLevel("0"); // 设置当前用户vip等级，必须为整型字符串
            roleInfo.setGameBalance(""+aEx.getMoneyNum()); // 角色现有金额
            roleInfo.setPartyName(""); // 设置帮派，公会名称
        roleInfo.setRoleCreateTime("1473141432"); // UC与1881渠道必传，值为10位数时间戳
                roleInfo.setPartyId("0"); // 360渠道参数，设置帮派id，必须为整型字符串
                roleInfo.setGameRoleGender("男"); // 360渠道参数
                roleInfo.setGameRolePower("0"); // 360渠道参数，设置角色战力，必须为整型字符串
                roleInfo.setPartyRoleId("0"); // 360渠道参数，设置角色在帮派中的id
                roleInfo.setPartyRoleName("帮主"); // 360渠道参数，设置角色在帮派中的名称
                roleInfo.setProfessionId("0"); // 360渠道参数，设置角色职业id，必须为整型字符串
                roleInfo.setProfession(""); // 360渠道参数，设置角色职业名称
                roleInfo.setFriendlist("无"); // 360渠道参数，设置好友关系列表，格式请参考：http://open.quicksdk.net/help/detail/aid/190
            com.quicksdk.User.getInstance().setGameRoleInfo(activity, roleInfo, true);
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
    public void app_onCreate(){
    }

    public void initSdk(){
        QuickSDK.getInstance().setIsLandScape( Boolean.getBoolean(SdkParams.get("isLandscape")));
//        try {
//            // check权限
//            if ((ContextCompat.checkSelfPermission(activity, Manifest.permission.READ_PHONE_STATE) != PackageManager.PERMISSION_GRANTED)
//                    || (ContextCompat.checkSelfPermission(activity, Manifest.permission.WRITE_EXTERNAL_STORAGE) != PackageManager.PERMISSION_GRANTED)) {
//                // 没有 ， 申请权限 权限数组
//                ActivityCompat.requestPermissions(activity, new String[] { Manifest.permission.READ_PHONE_STATE,
//                        Manifest.permission.WRITE_EXTERNAL_STORAGE }, 1);
//            } else {
//                // 有 则执行初始化
//                // 设置通知，用于监听初始化，登录，注销，支付及退出功能的返回值(必接)
//                initQkNotifiers();
//                // 请将下面语句中的第二与第三个参数，替换成QuickSDK后台申请的productCode和productKey值，目前的值仅作为示例
//                com.quicksdk.Sdk.getInstance().init(activity,SdkParams.get("product_code"),SdkParams.get("product_key"));
//            }
//        } catch (Exception e) {
//            // 异常 继续申请
//            ActivityCompat.requestPermissions(activity, new String[] { Manifest.permission.READ_PHONE_STATE,
//                    Manifest.permission.WRITE_EXTERNAL_STORAGE }, 1);
//        }
        initQkNotifiers();
        com.quicksdk.Sdk.getInstance().onCreate(activity);

    }
    public void act_onRequestPermissionsResult(int requestCode, String[] permissions, int[] grantResults) {
        if (grantResults[0] == PackageManager.PERMISSION_GRANTED) {
            //申请成功
            initQkNotifiers();
            com.quicksdk.Sdk.getInstance().init(activity,SdkParams.get("product_code"),SdkParams.get("product_key"));
        } else {
            //失败  这里逻辑以游戏为准 这里只是模拟申请失败 退出游戏    cp方可改为继续申请 或者其他逻辑
            System.exit(0);
            activity.finish();
        }
    }

    public void pay(String sname,PayParams aParams) {
        //步骤1：计算支付参数签名
        try{
            GameRoleInfo roleInfo = new GameRoleInfo();
            roleInfo.setServerID(aParams.getServerId());// 服务器ID，其值必须为数字字符串
            roleInfo.setServerName(aParams.getServerName());// 服务器名称
            roleInfo.setGameRoleName(aParams.getRoleName());// 角色名称
            roleInfo.setGameRoleID(aParams.getRoleId());// 角色ID
            roleInfo.setGameUserLevel(aParams.getRoleLevel()+"");// 等级
            roleInfo.setVipLevel(aParams.getVip());// VIP等级
            roleInfo.setGameBalance("");// 角色现有金额
            roleInfo.setPartyName("");// 公会名字

            OrderInfo orderInfo = new OrderInfo();
            orderInfo.setCpOrderID(aParams.getOrderID());// 游戏订单号
            orderInfo.setGoodsName(aParams.getProductName());// 产品名称
            orderInfo.setCount(1);// 购买数量，如购买"10元宝"则传10
            orderInfo.setAmount(aParams.getPrice()); // 总金额（单位为元）
            orderInfo.setGoodsID(aParams.getProductId()); // 产品ID，用来识别购买的产品
            orderInfo.setExtrasParams(""); // 透传参数

            com.quicksdk.Payment.getInstance().pay(activity, orderInfo, roleInfo);
        }
        catch (Exception ex){
            ex.printStackTrace();
        }
    }

    public void act_onStart() {
        // 生命周期接口调用(必接)
        com.quicksdk.Sdk.getInstance().onStart(activity);
    }

    public void act_onRestart() {
        // 生命周期接口调用(必接)
        com.quicksdk.Sdk.getInstance().onRestart(activity);
    }

    public void act_onPause() {
        // 生命周期接口调用(必接)
        com.quicksdk.Sdk.getInstance().onPause(activity);
    }

    public void act_onResume() {
        // 生命周期接口调用(必接)
        com.quicksdk.Sdk.getInstance().onResume(activity);
    }

    public void act_onStop() {
        // 生命周期接口调用(必接)
        com.quicksdk.Sdk.getInstance().onStop(activity);
    }
    public void act_onDestroy() {
        // 生命周期接口调用(必接)
        com.quicksdk.Sdk.getInstance().onDestroy(activity);
    }

    public void act_onNewIntent(Intent intent) {
        com.quicksdk.Sdk.getInstance().onNewIntent(intent);
    }

    public void act_onActivityResult(int requestCode, int resultCode, Intent data) {
        // 生命周期接口调用(必接)
        com.quicksdk.Sdk.getInstance().onActivityResult(activity, requestCode, resultCode, data);
    }
}
