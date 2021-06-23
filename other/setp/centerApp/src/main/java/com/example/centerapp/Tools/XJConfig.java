package com.example.centerapp.Tools;

import org.luaj.vm2.ast.Str;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Stack;

/*
    //单行注释 只支持单行注释
    单行字符串 “”
    多行字符串 [[]] [[ 和 ]] 各单占一行
    层级递进 {} 也是各单占一行
    支持类型 number boolean String table
    一行一个变量（非块内） table,分割
    运算符只支持 + 切只有字符串有效
    字符串支持 字符串+字符串
    例如：
    //这是注释
    a=23
    b=true
    a2=""
    root="E://dfsdfsd"
    cc =
    [[
    sdfsd
    xcvxc
    v]]
    ee =
    {
        a = false,
        h = 23,
        w = "",
        as = [[
        ]],
        true,"",111,true,
        yy = root + "xcvxc"
    }
    * */

public class XJConfig {
    FileTools ft;
    Map<String, Object> configTree = null;
    Object tempObject = null;

    public XJConfig(String path) {
        ft = new FileTools(path);
    }

    private String getFirstEndnChar(String str, int len) {

        if (str == "" || len < 0 || str.length() < (len * 2)) {

            return "";
        }

        String first = str.substring(0, len);
        String end = str.substring(str.length() - len, str.length());

        if (first.equals(end)) {

            return first;
        }
        return "";
    }

    private Map<String, Object> parse(String[] arrs) throws Exception {

        boolean block = false;
        String key = "";
        String tempValue = "";
        Map<String, Object> map = new HashMap<>();
        List<String> exStr = new ArrayList<>();

        int level = 0;

        for (String line : arrs) {
            Object obj = null;
            if (block == false) {

                String str = line;
                int index = str.indexOf("//");

                if (index == 0) {
                    continue;
                } else if (index > 0) {
                    str = str.substring(0, index - 1);
                }

                str = str.trim();

                if (str.length() == 0) {
                    continue;
                }

                if (str.length() > 1) {

                    index = str.indexOf("=");

                    if (index > 0) {

                        key = str.substring(0, index);
                        key = key.trim();
                        tempValue = str.substring(index + 1, str.length());
                        tempValue = tempValue.trim();

                        if (tempValue.equals("true") || tempValue.equals("false")) {

                            obj = tempValue.equals("true");
                        } else {
                            try {
                                obj = Double.parseDouble(tempValue);
                            } catch (NumberFormatException nfe) {
                            }
                        }
                        if (obj == null && getFirstEndnChar(tempValue, 1).equals("\"")) {

                            obj = tempValue.substring(1,tempValue.length()-1);
                        }

                        if (obj == null && tempValue.substring(0, 1).equals("{")) {//table

                            block = true;
                            level = 1;
                            exStr.clear();
                            continue;

                        } else if (obj == null && tempValue.substring(0, 2).equals("[[")) {//table

                            exStr.clear();
                            String first = tempValue.substring(2, tempValue.length());
                            if (first.length() > 0) {
                                exStr.add(first);
                            }
                            block = true;
                            level = -1;
                            continue;
                        }

                        if (obj == null) {

                            int idx = tempValue.indexOf("+");
                            if (idx > 0) {

                                String[] connects = tempValue.split("\\+");
                                List<String> list = new ArrayList<String>();
                                for (String item : connects) {
                                    list.add(item.trim());
                                }
                                obj = list;
                            } else
                                throw new Exception("error 1:" + line);
                        }

                        assert (obj != null);
                        if (map.containsKey(key)) {

                            throw new Exception("error 2:" + line);
                        }
                        map.put(key, obj);

                    }
                }
            } else {

                if (level == -1) {

                    String str = line;
                    if (!str.trim().equals("]]")) {

                        exStr.add(line);
                        continue;

                    } else {

                        String string = "";

                        for (String item : exStr) {
                            string = string + item + "\n";
                        }
                        string.substring(0, string.length() - 1);
                        if (map.containsKey(key)) {
                            throw new Exception("error 2:" + string);
                        }
                        map.put(key, string);
                        block = false;
                        level = 0;
                        exStr.clear();

                    }

                } else if (level > 0) {
                    //table 怎么解析？？？？？
                    throw new Exception("error 3: not supper table");
                }
            }
        }
        return map;
    }

    private void stringConnectHandle(final Map<String, Object> map, final StringFindBackKey sfbk) throws Exception {

        for (final String key : map.keySet()) {

            Object obj = map.get(key);
            if (obj.getClass() == ArrayList.class) {

                List<String> list = (List<String>) obj;
                String str = "";

                for (String item : list) {

                    String item1 = "";
                    if (getFirstEndnChar(item, 1).equals("\"")) {

                        str += item.substring(1, item.length() - 1);
                    } else {
                        str += sfbk.get(item);
                    }
                }
                map.put(key, str);

            } else if (obj.getClass() == Map.class) {

                final String curkey = key;
                Map<String, Object> map1 = (Map<String, Object>) obj;
                stringConnectHandle(map1, new StringFindBackKey() {
                    @Override
                    public String get(String key1) throws Exception {

                        if (!curkey.equals(key1)) {

                            if (map.containsKey(key)) {

                                Object val = map.get(key1);
                                if (val.getClass() == String.class) {

                                    return (String) val;
                                }
                                throw new Exception("error -1:" + key1);

                            } else {
                                return sfbk.get(key1);
                            }
                        } else {
                            throw new Exception("error -2:");
                        }
                    }
                });
            }

        }

    }

    public boolean parse() {

        if (ft.readAll() == false) {
            return false;
        }

        String[] strings = ft.readbuff2Lines();
        try {

            final Map<String, Object> config = parse(strings);
            stringConnectHandle(config, new StringFindBackKey() {
                @Override
                public String get(String key) throws Exception {
                    if (config.containsKey(key)) {

                        Object obj = config.get(key);
                        if (obj.getClass() == String.class) {
                            return (String) obj;
                        }
                        throw new Exception("eror -1:" + key);
                    }
                    throw new Exception("error -2:");
                }
            });
            configTree = config;

        } catch (Exception e) {
            e.printStackTrace();
            return false;
        }
        return true;
    }

    public Double getDouble(Object... objects) throws Exception {
        int type = getType(objects);
        if(type != 1)
            throw new Exception("Type error");

        return (Double)tempObject;
    }

    public boolean getBoolean(Object... objects) throws Exception {
        int type = getType(objects);
        if(type != 2)
            throw new Exception("Type error");

        return (Boolean) tempObject;
    }

    public String getString(Object... objects) throws Exception {
        int type = getType(objects);
        if(type != 3)
            throw new Exception("Type error");
        return (String) tempObject;
    }

    public Map<String,Object> getTable(Object... objects) throws Exception {
        int type = getType(objects);
        if(type != 4)
            throw new Exception("Type error");
        return (Map<String, Object>)tempObject;
    }

    public int getType(Object... objects) {
        try {
            if(configTree == null){
                parse();
            }
            tempObject = null;
            Object curobj = configTree;
            for (Object obj:objects) {
                String curkey = null;
                if(obj.getClass() == String.class )
                    curkey = (String)obj;
                else {

                    curkey = Integer.parseInt(""+obj)+"";
                    assert (!curkey.contains("."));
                    assert (!curkey.contains("-"));
                }
                if(curobj.getClass() == Map.class){
                    curobj = ((Map<String,Object>)curobj).get(curkey);

                }else{
                    return -1;
                }
            }
            Class cls = curobj.getClass();
            if(cls == Map.class)
                return 4;

            else if(cls == String.class)
                return 3;

            else if(cls == Boolean.class || cls == boolean.class )
                return 2;

            else{
                return 1;
            }

        }catch (Exception ex){
            ex.printStackTrace();
            return -1;
        }
    }

    public void clear() {
        ft.clear();
    }
}
