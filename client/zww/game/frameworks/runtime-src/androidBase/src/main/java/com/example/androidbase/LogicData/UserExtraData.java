package com.example.androidbase.LogicData;

import org.json.JSONException;
import org.json.JSONObject;

import java.util.HashMap;
import java.util.Map;

/* 用户扩展数据
        * 已经登录的角色相关数据
        * 有的渠道需要统计角色相关数据
        * @author xiaohei
        *
        */
public class UserExtraData {

    //	public static final int TYPE_SELECT_SERVER = 1;			//选择服务器
    public static final int TYPE_CREATE_ROLE = 1;			//创建角色
    public static final int TYPE_ENTER_GAME = 3;			//进入游戏
    public static final int TYPE_LEVEL_UP = 2;				//等级提升
    public static final int TYPE_EXIT_GAME = 5;				//退出游戏
    public static final int TYPE_ON_RECHARGE = 10;            //充值到帐
    public static final int TYPE_ON_EXCEPTION = 11;				//lua出现异常

    private int dataType;
    private String roleID;
    private String roleName;
    private String roleLevel;
    private int serverID;
    private String serverName;
    private float moneyNum;
    private long roleCTime;
    private String m_extraData;
    private String orString;
    private Map<String,String> otherValues = new HashMap<>();

    public String getOrString() {
        return orString;
    }
    public void setOrString(String orString) {
        this.orString = orString;
    }

    public int getDataType() {
        return dataType;
    }

    public void setDataType(int dataType) {
        this.dataType = dataType;
    }

    public String getRoleID() {
        return roleID;
    }

    public void setRoleID(String roleID) {
        this.roleID = roleID;
    }

    public String getRoleName() {
        return roleName;
    }

    public void setRoleName(String roleName) {
        this.roleName = roleName;
    }

    public String getRoleLevel() {
        return roleLevel;
    }

    public void setRoleLevel(String roleLevel) {
        this.roleLevel = roleLevel;
    }

    public int getServerID() {
        return serverID;
    }

    public void setServerID(int serverID) {
        this.serverID = serverID;
    }

    public String getServerName() {
        return serverName;
    }

    public void setServerName(String serverName) {
        this.serverName = serverName;
    }

    public float getMoneyNum() {
        return moneyNum;
    }

    public void setMoneyNum(float moneyNum) {
        this.moneyNum = moneyNum;
    }

    public long getRoleCTime() {
        return roleCTime;
    }

    public void setRoleCTime(long roleCTime) {
        this.roleCTime = roleCTime;
    }

    public String getExtraData() {
        return m_extraData;
    }

    public void setExtraData(String m_extraData) {
        this.m_extraData = m_extraData;
    }

    public void setOtherValues(Map<String,String> valueMap){

        otherValues = valueMap;

    }
    public String get(String key,String defaultValue){

        if(otherValues != null && otherValues.containsKey(key)){
            return otherValues.get(key);
        }

        return defaultValue;
    }
    public String AllParams(){
        String str = "";
        return str;
    }
}
