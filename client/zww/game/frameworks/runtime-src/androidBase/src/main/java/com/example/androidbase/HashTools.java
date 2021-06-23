package com.example.androidbase;

import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.io.StringWriter;
import java.lang.reflect.Array;
import java.util.Base64;
import java.util.Calendar;
import java.util.Date;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Locale;
import java.util.Map;
import java.util.Set;
import java.util.Timer;
import java.util.TimerTask;
import java.util.function.Function;

import android.app.Activity;
import android.content.Context;
import android.content.pm.ApplicationInfo;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.icu.text.TimeZoneFormat;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.os.Build;
import android.os.Bundle;
import android.provider.ContactsContract;
import android.telephony.TelephonyManager;
import android.util.DisplayMetrics;
import android.util.Log;
import android.view.Display;
import android.view.WindowManager;
import android.widget.Toast;

//import com.google.gson.Gson;

import androidx.annotation.RequiresApi;

import com.google.gson.Gson;

import org.json.JSONException;
import org.json.JSONObject;

public class HashTools {
    public final static String getTestUser = "";
    private static ApplicationInfo ai = null;
    private static String PackName = "";
    private static String MBName = "";
    private static  String IUrl = null;
    private static String path = "";
    private static  Activity _act = null;
    private static boolean islocalDataModify = false;
    private static  int PrivateState = 0;
    private static Map<String,Object> localFileData = null;
    final private static String TAG = "HashTools";
    static public void init(Activity act){
        try{
            localFileData = null;
            IUrl = null;
            _act = act;
            PackName = act.getPackageName();
            ai = act.getPackageManager().getApplicationInfo( PackName,PackageManager.GET_META_DATA);
            String url = getMetaKeyData("Error2ServerUrl");
            if(url == null || url.equals("")){
                IUrl = getMetaKeyData("DyLogUrl");
                if(IUrl != null && IUrl.equals(""))
                    IUrl = null;
                if(IUrl != null){
                    path = "N"+act.getFilesDir().getAbsolutePath() + "/waitno.log";
                    File fie = new File(path.substring(1,path.length()),"r");
                    if(fie.exists()){
                        fie.delete();
                    }
                }
            }
            MBName = getMetaKeyData("MBName");
        }catch(Exception ex){
            MBName = PackName;
        }
        finally{
            if(MBName == null || MBName.equals(""))
                MBName = PackName;
        }
    }
    //以下系列根据上架标准的部分来判断包名实现
    //-1 判断不了获取包名失败 1 是指定渠道包 0不是指定渠道包

    static public int pIsOppo(){
        if(PackName == "")
            return -1;
        if(getosChannel().equals("oppo"))
            return 1;
        return 0;

    }
    static public String getMetaKeyData(String key){
        if(ai == null)
            return null;
        return ai.metaData.getString(key);
    }
    static public String getMBName(){
        return MBName;
    }
//    static public void InitCrashHandler(Context context){
//        String url = getMetaKeyData("Error2ServerUrl");
//        if (url != null && !url.equals("") && CrashHandler.url == null){
//            CrashHandler.url = url;
//            CrashHandler.getInstance().init(context);
//        }
//    }
//    static public boolean checkInsidePersonAndPack(String ParamJson,InsidePersonAndPackBackFun fun){
//        return false;
//    }
    static public boolean isUInt(String str){
        try{
            Integer temp = Integer.parseInt(str);
            return str.equals(""+temp);
        }catch (Exception ex){
            return false;
        }
    }
    static public boolean isDobule(String str){
        try{
            Double temp = Double.parseDouble(str);
            return str.equals(""+temp);
        }catch (Exception ex){
            return false;
        }
    }
    static public boolean setLogHoot(){
        if(IUrl == null){
            return false;
        }
        return false;
    }
    static public boolean setUnLogHoot(){
        if(IUrl == null)
            return false;
        return false;
    }
    static public boolean CheckPackageInfoExist(Activity act,String Name){
        try{
            PackageInfo pif = act.getPackageManager().getPackageInfo(Name,0);
            if(pif.equals(null))
                return false;
            return true;
        }catch (Exception ex){
            return false;
        }
    }
    public static String getResStr(int paramid)
    {
        return _act.getString(paramid);
    }
    public static String getResValueString(String key,String defaultValue){
        int resid = _act.getResources().getIdentifier(key,"string",PackName);
        if(resid == 0)
            return defaultValue;
        return _act.getString(resid);
    }
    public static String getResValueString(Context con, String key,String defaultValue){
        Log.d("ddt",key + " A1");
        String curPackName = con.getPackageName();
        int resid = con.getResources().getIdentifier(key,"string",curPackName);
        Log.d("ddt",key + " A2");
        if(resid == 0)
            return defaultValue;
        return con.getString(resid);
    }
    private static String readSteamInfo(InputStream inputStream){
        try {
            BufferedReader reader= new BufferedReader(new InputStreamReader(inputStream));
            String line;
            String ret = "";
            while ((line = reader.readLine())!= null){
                ret = ret+line+"\n";
            }
            return ret;
        }catch (Exception ex){
            return "";
        }
    }
    public static boolean pingHost(String str){
        return pingHost(str,5);
    }
    public static boolean pingHost(String str,int MaxTime) {  //str  为要ping的IP地址
        boolean result = false;
        try {
            Process p = Runtime.getRuntime().exec("ping -c 1 -w "+MaxTime+" " + str);
            int status = p.waitFor();
            if (status == 0) {
                result = true;
            }
            else {
                result = false;
            }
            Log.d("ddt2","ping "+str);
            if(result){
                Log.d("ddt2",readSteamInfo(p.getInputStream()));
            }else{
                Log.d("ddt2",readSteamInfo(p.getInputStream()));
                Log.d("ddt2",readSteamInfo(p.getErrorStream()));
            }
        }
        catch (IOException e) {e.printStackTrace();}
        catch (InterruptedException e) {e.printStackTrace();}
        return result;
    }
    //@RequiresApi(api = Build.VERSION_CODES.O)
    static public String readFileAll(String path)  {

        FileInputStream fis = null;
        String ret = "";
        try{

            fis = new FileInputStream(path);
            //String mreadbuff = fis.readAllBytes();
            final int len = 4096;
            int uselen = 0;
            byte[] buffer = new byte[len];
            do{
                uselen = fis.read(buffer,0,len);
                if(uselen > 0){
                    //byte[] bytes = buffer.clone(uselen);
                    String temp = "";
                    if((uselen) == len){
                        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
                            temp = Base64.getEncoder().encodeToString(buffer);
                        }else{
                            temp = new String(buffer);
                        }
                    }else{
                        byte[] bytes = new byte[uselen];
                        System.arraycopy(buffer,0,bytes,0,uselen);
                        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
                            temp = Base64.getEncoder().encodeToString(bytes);
                        }else{
                            temp = new String(bytes,"utf-8");
                        }
                    }
                    ret = ret + temp;
                }
            }while (uselen > 0);
            fis.close();
            fis = null;

        }catch (Exception ex){

            ret = null;
            ex.printStackTrace();
            if(fis != null) {

                try {
                    fis.close();
                }catch (Exception e){
                }
            }

        }finally {

        }

        return ret;
    }
    static public void test0034(
            int a,float b,double d,
            long c,short e,boolean bo,
            Float fl,Integer in,Long lo,
            Short sh,Double dou,Boolean Bo,
            String str
    ){
        Log.d("testfun","param1 = ("+a+","+b+","+d+","+c+","+e+(bo ? "true":"false"));
        Log.d("testfun","param2 = ("+fl+","+in+","+lo+","+sh+","+"dou"+(Bo ? "true":"false"));
        Log.d("testfun","param3 = ("+str);
        Log.d("testfun","end");
        return ;
    }
    //static public boolean ReadFile(String path,)
    static public boolean WriteFile(String path,String context,Activity activity){
        if(activity == null)
            activity = _act;

        FileOutputStream outputStream = null;
        try{

            outputStream = new FileOutputStream(path);
            byte[] bytes = context.getBytes();
            outputStream.write(bytes);

        }catch (Exception ex){
            ex.printStackTrace();
        }finally {

            try {
                outputStream.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
            return true;
        }
    }
    //从assets拷贝到可写目录的对应文件夹下
    static public boolean CopyFile(String path,Activity activity,Boolean isOver){
        if(activity == null)
            activity  = _act;
        String srcPath =activity.getExternalFilesDir("").getAbsolutePath();
        File file = new File(srcPath+"/"+path);
        if(file.exists() == true && isOver == false){
            return true;
        }
        if(isOver == false)
            file.delete();
        try {
            InputStream inputStream = activity.getAssets().open(path);
            assert (file.createNewFile());
            FileOutputStream fos = new FileOutputStream(file);
            final int len = 4096;
            int uselen = 0;
            byte[] buffer = new byte[len];
            do{
                uselen = inputStream.read(buffer,0,len);
                if(uselen > 0){
                    fos.write(buffer,0,uselen);
                }
            }while (uselen > 0);
            inputStream.close();
            fos.close();
        } catch (IOException e) {
            sdkPoolManage.getInstance().printStackTrace(TAG,e);
            return false;
        }
        return true;
    }
    static public String EnCode(String str){
        return "";
    }
    static public String DeCode(String str){
        return "";
    }
    static public boolean CopyFile(String src, String obj, boolean isDelete) {
        File f1 = new File(src);
        File f2 = new File(obj);
        Log.d("ddt2", "CopyFile src" + src + "    obj = " + obj);
        Log.d("ddt2", "CopyFile a");
        if (f1.exists() == false) {
            Log.d("ddt2", "CopyFile -1");
            return false;
        }
        Log.d("ddt2", "CopyFile b");
        if (f1.isDirectory() == true) {
            Log.d("ddt2", "CopyFile -2");
            return false;
        }
        Log.d("ddt2", "CopyFile c");
        File start = new File(src);
        File end = new File(obj);
        Log.d("ddt2", "CopyFile 1");
        BufferedInputStream bis=null;
        BufferedOutputStream bos=null;
        Log.d("ddt2", "CopyFile 2");
        try {
            bis=new BufferedInputStream(new FileInputStream(start));
            bos=new BufferedOutputStream(new FileOutputStream(end));
            Log.d("ddt2", "CopyFile 3");
            int len = 0;
            int size = 0;
            byte[] flush = new byte[40960];
            Log.d("ddt2", "CopyFile 4");
            while((len=bis.read(flush)) != -1) {
                bos.write(flush, 0, len);
                size = size + len;
                Log.d("ddt2", "CopyFile 5 size = "+size);
            }
            Log.d("ddt2", "CopyFile 6");
            bos.flush();
            Log.d("ddt2", "CopyFile 7");
        }catch(FileNotFoundException e) {
            e.printStackTrace();
        }catch(IOException e) {
            e.printStackTrace();
        }finally {
            try {
                Log.d("ddt2", "CopyFile 8");
                if(bos != null)
                    bos.close();
                Log.d("ddt2", "CopyFile 9");
                if(bis != null)
                    bis.close();
                Log.d("ddt2", "CopyFile 10");
            }catch (Exception io){
                io.printStackTrace();
            }
        }
        Log.d("ddt2", "CopyFile 11");
        return  false;
    }
    static public int packageCode(Context context,int defCode) {
        PackageManager manager = context.getPackageManager();
        int code = defCode;
        try {
            PackageInfo info = manager.getPackageInfo(context.getPackageName(), 0);
            code = info.versionCode;
        } catch (PackageManager.NameNotFoundException e) {
            e.printStackTrace();
        }
        return code;
    }
    static public Map<String,Object> readLocalFile(){
		if(localFileData == null){
			FileInputStream fis = null;
			try {
				fis = _act.openFileInput("localTempDatas.ajson");//与写入对应写入时起的文件名，这里用写入时的名字读取的就是写入时的数据
				ByteArrayOutputStream baos = new ByteArrayOutputStream();
				byte[] buffer = new byte[1024];
				int len = 0;
				while ((len = fis.read(buffer)) != -1){
					baos.write(buffer,0,len);
				}
				fis.close();
				String str = baos.toString();
				Gson gson = new Gson();
				Map<String,Object> ret = gson.fromJson(str,Map.class);
				Set<String> keySet = ret.keySet();
				Iterator<String> it = keySet.iterator();
				localFileData = new HashMap<>();
				while (it.hasNext()) {
					String key = it.next();
					localFileData.put(key,ret.get(key));
				}

			} catch (Exception e) {
				e.printStackTrace();
			}
		}
		if(localFileData == null){
			return null;
		}
		Map<String,Object> retback = new HashMap<>();
		Set<String> keySet = localFileData.keySet();
		Iterator<String> it = keySet.iterator();
		while (it.hasNext()) {
			String key = it.next();
			retback.put(key,localFileData.get(key));
		}
		return retback;
    }
    static public boolean updateLocalFileByKey(String key,Object val){
		if(localFileData == null){
			readLocalFile();
		}
		if(localFileData == null)
			localFileData = new HashMap<>();
		if(val != null && localFileData.containsKey(key)){
			if(val.equals(localFileData.get(key)))
				return true;
		}
		if(val != null)
			Log.d("ddt2","updateLocalFileByKey Key:"+key+" val:"+val);
		islocalDataModify = true;
		String prvestr1 = null;
		Gson gson = new Gson();
		try{
			prvestr1 =  gson.toJson(localFileData);
		}catch (Exception ex){
			ex.printStackTrace();
		}finally {
			localFileData.put(key,val);
			String str2 = null;
			try{
				str2 =  gson.toJson(localFileData);//验证有效性，防止因为更新表后字符串失败，后边没法恢复。存入文件残缺更大
				return true;
			}catch (Exception ex){
				ex.printStackTrace();
				if(prvestr1 != null)
				{
					localFileData = gson.fromJson(prvestr1,Map.class);
				}else
					localFileData.put(key,null);
				return false;
			}finally {
			}
		}
    }
    static public boolean saveLocalFile(){
		Gson gson = new Gson();
		if(localFileData == null)
			return true;
		FileOutputStream fos = null;
		try{
			String str = gson.toJson(localFileData);
			fos = _act.openFileOutput("localTempDatas.ajson", Context.MODE_PRIVATE);
			fos.write(str.getBytes());
			fos.close();
			islocalDataModify = false;
			Log.d("ddt2", "saveLocalFile: save file localTempDatas.ajson success");
			return true;
		}catch (Exception ex){
			ex.printStackTrace();
			return false;
		}
    }

    //operator	是	string	网络运营商名字（例如China Mobile GSM、Orange EG）
    public static String getOperatorName() {
        /*
         * getSimOperatorName()就可以直接获取到运营商的名字
         * 也可以使用IMSI获取，getSimOperator()，然后根据返回值判断，例如"46000"为移动
         * IMSI相关链接：http://baike.baidu.com/item/imsi
         */
        TelephonyManager telephonyManager = (TelephonyManager) _act.getSystemService(Context.TELEPHONY_SERVICE);
        // getSimOperatorName就可以直接获取到运营商的名字
        return telephonyManager.getNetworkOperator();
    }
//    public static String getNetworkState() {
//        ConnectivityManager connManager = (ConnectivityManager) _act.getSystemService(Context.CONNECTIVITY_SERVICE); // 获取网络服务
//        if (null == connManager) { // 为空则认为无网络
//            return "NULL";
//        }
//        // 获取网络类型，如果为空，返回无网络
//        NetworkInfo activeNetInfo = connManager.getActiveNetworkInfo();
//        if (activeNetInfo == null || !activeNetInfo.isAvailable()) {
//            return "NULL";
//        }
//        // 判断是否为WIFI
//        NetworkInfo wifiInfo = connManager.getNetworkInfo(ConnectivityManager.TYPE_WIFI);
//        if (null != wifiInfo) {
//            NetworkInfo.State state = wifiInfo.getState();
//            if (null != state) {
//                if (state == NetworkInfo.State.CONNECTED || state == NetworkInfo.State.CONNECTING) {
//                    return "WIFI";
//                }
//            }
//        }
//        // 若不是WIFI，则去判断是2G、3G、4G网
//        TelephonyManager telephonyManager = (TelephonyManager) _act.getSystemService(Context.TELEPHONY_SERVICE);
//        int networkType = telephonyManager.getNetworkType();
//        switch (networkType) {
//            /*
//             */
//            // 2G网络
//            case TelephonyManager.NETWORK_TYPE_GPRS:
//            case TelephonyManager.NETWORK_TYPE_CDMA:
//            case TelephonyManager.NETWORK_TYPE_EDGE:
//            case TelephonyManager.NETWORK_TYPE_1xRTT:
//            case TelephonyManager.NETWORK_TYPE_IDEN:
//                return "2G";
//            // 3G网络
//            case TelephonyManager.NETWORK_TYPE_EVDO_A:
//            case TelephonyManager.NETWORK_TYPE_UMTS:
//            case TelephonyManager.NETWORK_TYPE_EVDO_0:
//            case TelephonyManager.NETWORK_TYPE_HSDPA:
//            case TelephonyManager.NETWORK_TYPE_HSUPA:
//            case TelephonyManager.NETWORK_TYPE_HSPA:
//            case TelephonyManager.NETWORK_TYPE_EVDO_B:
//            case TelephonyManager.NETWORK_TYPE_EHRPD:
//            case TelephonyManager.NETWORK_TYPE_HSPAP:
//                return "3G";
//            // 4G网络
//            case TelephonyManager.NETWORK_TYPE_LTE:
//                return "4G";
//            default:
//                return "MOBILE";
//        }
//    }
    //获取时区
    public static String getTimeArea(){
        Calendar cal = Calendar.getInstance(Locale.getDefault());
        int zoneOffset = cal.get(java.util.Calendar.ZONE_OFFSET);
        int zone = zoneOffset / 60 / 60 / 1000;// 时区，东时区数字为正，西时区为负
        return ""+zone;
    }
//    public static String getappVersionName(){
//        return CrashHandler.getVersionName(_act);
//    }
//    public static String getappVersionCode(){
//        return ""+CrashHandler.getVersionCode(_act);
//    }
    public static String getDeviceType(){
        //String DevDir = TransleDirName(Build.MANUFACTURER.toString()+ "_" +Build.BRAND.toString() +"_" +Build.MODEL.toString());
        String deviceType = "";
        try{
            deviceType = Build.BRAND.toString()+"-"+Build.MODEL.toString();
        }catch (Exception ex){
            ex.printStackTrace();
        }
        return deviceType;
    }
    //google  oppo huawei
    public static String getosChannel(){
        String channel = "google";
        try{
            String[] strs = PackName.split("\\.");
            String laststr = strs[strs.length-1];
            if(laststr == ".huawei" || laststr == ".HUAWEI"){
                //https://developer.huawei.com/consumer/cn/doc/development/AppGallery-connect-Guides/appgallerykit-preparation-game-0000001055356911
                channel = "huawei";
            }else if(laststr == ".nearme.gamecenter"){
                //https://open.oppomobile.com/wiki/doc#id=10004
                channel = "oppo";
            }
        }catch (Exception ex){
        }
        return channel;
    }
    public static String getosVersion(){
        return Build.VERSION.RELEASE;
    }
    public static String getosType(){
        return "google";
    }
    public static String getDeviceCategory(){
        String str = "telePhone";
        try{
            WindowManager wm = (WindowManager) _act.getSystemService(Context.WINDOW_SERVICE);
            Display display = wm.getDefaultDisplay();
            DisplayMetrics dm = new DisplayMetrics();
            display.getMetrics(dm);
            double x = Math.pow(dm.widthPixels / dm.xdpi, 2);
            double y = Math.pow(dm.heightPixels / dm.ydpi, 2);
            double screenInches = Math.sqrt(x + y); // 屏幕尺寸
            if(screenInches >= 7)
                str = "pad";
        }catch (Exception ex){
            ex.printStackTrace();
        }finally {
            return str;
        }

    }

}
