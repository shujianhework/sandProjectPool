package com.example.tsixivivo;

import android.app.Activity;
import android.content.Context;

import com.vivo.unionsdk.open.OrderResultEventHandler;
import com.vivo.unionsdk.open.OrderResultInfo;
import com.vivo.unionsdk.open.QueryOrderCallback;
import com.vivo.unionsdk.open.VivoPayCallback;
import com.vivo.unionsdk.open.VivoPayInfo;
import com.vivo.unionsdk.open.VivoQueryOrderInfo;
import com.vivo.unionsdk.open.VivoRoleInfo;
import com.vivo.unionsdk.open.VivoUnionSDK;

import java.util.HashMap;


public class VivoUnionHelper {
    private static final String TAG = "VivoUnionHelper";

    /**
     * 初始化sdk
     *
     * @param context
     * @param debug
     */
    public static void initSdk(Context context, boolean debug) {
        VivoUnionSDK.initSdk(context, VivoConstant.APP_ID, debug);
    }

    /**
     * 查询订单状态
     *
     * @param cpOrderNumber cp订单号
     * @param vivoTransNo   vivo订单号
     * @param price         价格
     */
    public static void queryOrderResult(String cpOrderNumber, String vivoTransNo, String price, QueryOrderCallback queryOrderCallback) {
        final HashMap<String, String> params = new HashMap<>();
        params.put(VivoConstant.APP_ID_PARAM, VivoConstant.APP_ID);
        params.put(VivoConstant.CP_ID_PARAM, VivoConstant.CP_ID);
        params.put(VivoConstant.CP_ORDER_NUMBER, cpOrderNumber);
        params.put(VivoConstant.ORDER_NUMBER, vivoTransNo);
        params.put(VivoConstant.ORDER_AMOUNT, price);
        params.put(VivoConstant.VERSION, "1.0.0");
        final String signature = VivoSignUtils.getVivoSign(params, VivoConstant.APP_KEY);

        VivoQueryOrderInfo.Builder builder = new VivoQueryOrderInfo.Builder(signature);
        builder.appId(VivoConstant.APP_ID)
                .cpId(VivoConstant.CP_ID)
                .cpOrderNumber(cpOrderNumber)
                .orderNumber(vivoTransNo)
                .orderAmount(price);

        VivoUnionSDK.queryOrderResult(builder.build(), queryOrderCallback);
    }

    /**
     * 登录成功后上报角色信息
     *
     * @param vivoRoleInfo 角色信息
     */
    public static void reportRoleInfo(VivoRoleInfo vivoRoleInfo) {
        VivoUnionSDK.reportRoleInfo(vivoRoleInfo);
    }

    /**
     * 查询是否有调单
     *
     * @param orderResultEventHandler
     */
    public static void registerOrderResultEventHandler(OrderResultEventHandler orderResultEventHandler) {
        VivoUnionSDK.registerOrderResultEventHandler(orderResultEventHandler);
    }


    /**
     * 直接吊起微信与支付宝
     *
     * @param activity
     * @param mVivoPayCallback 支付结果回调
     * @param code             1表示微信，2表示支付宝
     */
    public static void payNowV2(Activity activity, VivoPayInfo vivoPayInfo, VivoPayCallback mVivoPayCallback, int code) {
        VivoUnionSDK.payNowV2(activity, vivoPayInfo, mVivoPayCallback, code);
    }

    /**
     * 吊起支付面板
     *
     * @param activity
     * @param mVivoPayCallback 支付结果回调
     */
    public static void payV2(Activity activity, VivoPayInfo vivoPayInfo, VivoPayCallback mVivoPayCallback) {
        VivoUnionSDK.payV2(activity, vivoPayInfo, mVivoPayCallback);
    }


    /**
     * 登录
     *
     * @param activity
     */
    public static void login(Activity activity) {
        VivoUnionSDK.login(activity);
    }

    /**
     * 游戏方补单成功主动通知联运
     *
     * @param orderResultInfo
     */
    public static void sendCompleteOrderNotification(OrderResultInfo orderResultInfo) {
        VivoUnionSDK.sendCompleteOrderNotification(orderResultInfo);
    }


//


}
