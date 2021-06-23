package com.example.androidbase;

import android.app.Activity;
import android.app.Application;
import android.nfc.Tag;
import android.os.Build;

//import com.example.tools.AESUtils;
//import com.example.tools.FileTools;

import java.io.File;
import java.lang.reflect.Method;
import java.lang.reflect.Modifier;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class Java2native {
    static Java2native instance = null;
    static private int classTreeState = 0;
    private static String TAG = "Java2native";
    private static String aesClassTimeStamp = "";
    static private Map<String,List<List<String>> > allClassByMethon = new HashMap<>();
    public static Java2native getInstance(){

        if(instance == null){

            synchronized (Java2native.class){

                if(instance == null)

                    instance = new Java2native();
            }
            sdkPoolManage.getInstance();
        }

        return instance;
    }
    private Java2native(){
    }

    public java.lang.String getAesClassTimeStamp() {
        return aesClassTimeStamp;
    }
    public int getClassTreeState(){
        return classTreeState;
    }

    public String typeGetFunAutographKey(String type){
        switch (type) {
            case "int":
                return "I";
            case "float":
                return "F";
            case "double":
                return "D";
            case "class java.lang.String":
                return "Ljava/lang/String;";
            case "void":
                return "V";
            case "short":
                return "S";
            case "boolean":
                return "Z";
            case "long":
                return "J";
            case "class java.lang.Float":
                return "Ljava/lang/Float;";
            case "class java.lang.Integer":
                return "Ljava/lang/Integer;";
            case "class java.lang.Long":
                return "Ljava/lang/Long;";
            case "class java.lang.Short":
                return "Ljava/lang/Short;";
            case "class java.lang.Double":
                return "Ljava/lang/Double;";
            case "class java.lang.Boolean":
                return "Ljava/lang/Boolean;";
            default:
                return "";
        }

    }
    //map[函数名] = {类名,返回值类型,...(参数列表)}
    private Map<String, List<String>> getClassAllStaticPublicMethonFun(String className) throws ClassNotFoundException {

        Method[] methods = Class.forName(className).getMethods();
        Map<String,List<String>> ret = new HashMap<>();
        sdkPoolManage sdkPool = com.example.androidbase.sdkPoolManage.getInstance();
        for (Method method:methods) {

            int modifier = method.getModifiers();
            if(Modifier.isStatic(modifier) && Modifier.isPublic(modifier)){

                sdkPool.log(TAG,"test ----------------------");
                String methodName = method.getName();
                sdkPool.log(TAG,"function:"+className+"->"+methodName);
                sdkPool.log(TAG,method.getReturnType().toString());
                Class[] classes = method.getParameterTypes();
                List<String> list = new ArrayList<>();
                list.add(className);
                list.add(method.getReturnType().toString());

                for (Class item:classes) {
                    sdkPool.log(TAG,item.toString());
                    list.add(item.toString());
                }

                if(allClassByMethon.containsKey(methodName) == false)
                    allClassByMethon.put(methodName,new ArrayList<>());
                allClassByMethon.get(methodName).add(list);

            }
        }
        return ret;
    }
    public void setActivity(Activity activity){

        sdkPoolManage.getInstance().setActivity(activity);
        if(classTreeState == 0){
            classTreeState = 1;
            try {

                Method method =  activity.getClass().getMethod("getAesEncodeInfo");
                Map<String,String> map =  (Map<String,String>)method.invoke(activity);
                Method method1 = activity.getClass().getMethod("setNativeInfos",String.class,Map.class);
                allClassByMethon.clear();
                if(method1 == null)
                    return ;
                String out = "";
                if(map.size() > 0 && map.containsKey("in") && map.containsKey("out") && map.containsKey("key")){

                    String in = map.get("in");
                    out = map.get("out");
                    String key = map.get("key");
                    Map<String,Map<String,List<String>>> allClassTree = new HashMap<>();

                    if(in.length() > 0 && out.length() > 0 && key.length() > 0){
                        String str = "";
                        if(false) {
                            //AESUtils.decryptFile(new File(in), new File(out), key.getBytes(), true);
                            //str = AESEncryptor.decrypt(key, in);
                        }else{
                            str = HashTools.readFileAll(in);
                        }
                        String[] lines = str.split("\r\n");

                        //第一行是时间标记
                        if(lines.length > 1){

                            aesClassTimeStamp = lines[0].substring(12);
                            String srcData = HashTools.readFileAll(out);//activity.getExternalFilesDir("").getCanonicalPath() + "/native.jlua");
                            if(srcData != null && srcData.length() > 0){
                                int firstNewLine = srcData.indexOf("\n");
                                String firstLine = srcData.substring(0,firstNewLine-1);
                                Method method2 = activity.getClass().getMethod("checkTimeFlg",String.class,String.class);
                                sdkPoolManage.getInstance().log(TAG,"call activity->checkTimeFlg");
                                Boolean isNewMake = (Boolean)method2.invoke(activity,aesClassTimeStamp,firstLine);
                                sdkPoolManage.getInstance().log(TAG,"call activity->checkTimeFlg => "+isNewMake.toString());
                                if(isNewMake == true){
                                    classTreeState = 2;
                                    return;
                                }
                            }

                            for (int i = 2; i < lines.length; i++) {
                                getClassAllStaticPublicMethonFun(lines[i]);
                            }
                        }
                    }

                }

                if(allClassByMethon.size() > 0){
                    String data = (String)method1.invoke(activity,aesClassTimeStamp,allClassByMethon);
                    if(data != null && data.length()> 0) {
                        HashTools.WriteFile(
                                //activity.getExternalFilesDir("").getCanonicalPath() + "/native.jlua",
                                out,
                                data, activity);
                        classTreeState = 2;
                    }

                }

            }catch (Exception ex){

                allClassByMethon.clear();
                sdkPoolManage.getInstance().printStackTrace(TAG,ex);

            }
        }

    }
}
