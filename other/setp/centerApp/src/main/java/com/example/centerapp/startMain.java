package com.example.centerapp;

import com.example.centerapp.Components.ComponentManage;
import com.example.centerapp.Tools.FileTools;
import com.example.centerapp.Tools.XJConfig;
import com.example.centerapp.record.Log;

import org.luaj.vm2.Globals;
import org.luaj.vm2.LuaValue;
import org.luaj.vm2.ast.Str;
import org.luaj.vm2.lib.jse.JsePlatform;

import java.io.File;
import java.io.IOException;
import java.security.Key;
import java.util.HashMap;
import java.util.Map;

public class startMain {
    public static Map<String,String> cmdParam = new HashMap<>();
    public static XJConfig configParam = null;


    static public boolean selfProcessExist(){
        return false;
    }


    static public void handleCmds(String[] args){
        try {
            Log.debug("handleCmds 1");
            String key = "";

            for (int i = 0; i < args.length; i++) {

                Log.debug(args[i]);

                if ( i % 2 == 0){

                    key = "";
                    String item = args[i];
                    String first = item.substring(0,1);

                    if(first.equals("-") || first.equals("/")){
                        item = item.substring(2,item.length());
                    }

                    if(item.length() > 0){

                        if( !item.contains("=") ){
                            key = item.toLowerCase();
                        }
                    }

                }else if(key.length() > 0){

                    cmdParam.put(key,args[i]);
                }
            }

            Log.debug("handleCmds 2");

        }catch (Exception ex){

            ex.printStackTrace();
        }
    }
    static public boolean readConfig(){

        String path = "config.XJ";
        boolean block = false;
        int blockIndex = 0;

        if(cmdParam.containsKey("config")){
            path = cmdParam.get("config");
        }

        assert (path.length() > 4);

        if( path.contains(":") == false ){

             path = System.getProperty("user.dir")+"\\"+path;
        }

        XJConfig xjc = new XJConfig(path);
        if(xjc.parse() == false){
            xjc.parse();
            return false;
        }
        configParam = xjc;
        return true;
    }

    static public boolean loadTools(){

        if(configParam == null)
            return false;

        if(ComponentManage.getInstance().setConfig(configParam) == false) {
            ComponentManage.getInstance().clear();
            return false;
        }

        return true;
    }
    static public void start(){
    }
    static public void loop(){
    }
    static public void end(){
    }
    static public void unLoadTools(){
    }

    //a=b c=d
    static public void main(String[] args){
        System.out.println(System.getProperty("user.dir"));
        File directory = new File("");
        try {
            System.out.println(directory.getCanonicalPath());
            System.out.println(directory.getAbsolutePath());
        } catch (IOException e) {
            e.printStackTrace();
        }
        if (selfProcessExist() == false){

            handleCmds(args);
            if ( readConfig() == true) {

                loadTools();
                start();
                loop();
                end();
                unLoadTools();
            }
        }
//        String luaStr = "print [[this is a test server and client]]";
//        Globals globals = JsePlatform.standardGlobals();
//        LuaValue luaValue = globals.load(luaStr);
//        luaValue.call();
//        LuaValue luaValue2 = globals.loadfile("test.lua");
//        luaValue2.call();
    }
}