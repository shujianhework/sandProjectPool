package com.example.centerapp.Components;

import com.example.centerapp.Tools.MessageNotifyData;
import com.example.centerapp.Tools.MessageNotifyFun;
import com.example.centerapp.Tools.XJConfig;
import com.google.gson.Gson;

import java.lang.reflect.InvocationTargetException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class ComponentManage {

    static private Map<String,ComponentBase> components;
    static private volatile ComponentManage instance = null;
    static private Map<String, List<MessageNotifyData> > queue = new HashMap<>();
    //static private Map<String, MessageNotifyFun> handles = new HashMap<>();

    private ComponentManage(){}

    public static ComponentManage getInstance(){

        if(instance == null){

            synchronized (ComponentManage.class){

                if(instance == null)

                    instance = new ComponentManage();
            }
        }

        return instance;
    }
    public static Object newObj(String className, Object... args) throws ClassNotFoundException, NoSuchMethodException, IllegalAccessException, InvocationTargetException, InstantiationException {
        Class[] classes = new Class[args.length];
        for (int i = 0; i < classes.length; i++) {
            classes[i] = args[i].getClass();
        }
        Object obj = null;
        obj = Class.forName(className).getConstructor(classes).newInstance(args);
        return obj;
    }
    public boolean setConfig(XJConfig config){
        List<String> tools = new ArrayList<>() ;
        tools.add("LuaComponentManage");
        try {
            String exTools = config.getString("ExTools");
            Gson gson = new Gson();
            List<String> list = gson.fromJson(exTools,List.class);
            for (String item:list) {
                tools.add(item);
            }
        }catch (Exception ex){
            ex.printStackTrace();
        }
        try {
            for (String item :tools) {
                ComponentBase componentBase = (ComponentBase)newObj(""+item);
                String name = componentBase.getName();

            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return true;
    }

    public void close(String name){

        if(components.containsKey(name)){

            if(queue.containsKey(name)){
                queue.get(name).clear();
            }
            components.get(name).close();
        }
    }

    public void clear(){

        for (String name: components.keySet()) {

            if(queue.containsKey(name)){
                queue.get(name).clear();
            }
            components.get(name).close();

        }
    }

    public void update(String name){
        //谁来update 就是默认它对应的线程运行时候
        update(name,-1);
    }
    public void update(String name,int maxPush){

        if(maxPush == -1 || maxPush < 1000){

            if(queue.containsKey(name) && components.containsKey(name)){

                List<MessageNotifyData> msgs = queue.get(name);
                List<MessageNotifyData> tempRun = new ArrayList<>();

                synchronized (msgs){

                    int msgsLen = msgs.size();
                    if(maxPush == -1){

                        maxPush = msgs.size();
                    }

                    for (int i = 0; i < maxPush; i++) {
                        if(i == maxPush || i == msgsLen){
                            break;
                        }
                        tempRun.add(msgs.get(0));
                        msgs.remove(i);
                    }
                }

                ComponentBase cb = components.get(name);

                for (MessageNotifyData data:tempRun) {
                    try {

                        cb.onMessageHandle(data);

                    }catch (Exception ex){
                    }
                }
                tempRun.clear();

            }
        }
    }

    public boolean send(MessageNotifyData data){

        String toolName = data.toolName;
        if(toolName == null || data.name == null || components.containsKey(toolName)){
            return false;
        }

        if(queue.containsKey(toolName) == false)
            queue.put(toolName, new ArrayList<MessageNotifyData>());

        List list = queue.get(toolName);

        synchronized (list){
            list.add(data);
        }

        return true;
    }

}
