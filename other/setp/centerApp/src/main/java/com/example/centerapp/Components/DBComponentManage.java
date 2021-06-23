package com.example.centerapp.Components;

import com.example.centerapp.Tools.MessageNotifyData;
import com.example.centerapp.Tools.MessageNotifyFun;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.Date;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class DBComponentManage implements ComponentBase {
    private static final String DRIVER = "com.microsoft.sqlserver.jdbc.SQLServerDriver";
    static private DBComponentManage instance;
    private Map<String,Connection> db_pools = new HashMap<>();
    @Override
    public String getName() {
        return "DBComponentManage";
    }

    @Override
    public void open() {

    }

    @Override
    public void close() {

        List<String> keys = new ArrayList<>();

        for (String key:db_pools.keySet()) {
            keys.add(key);
        }

        for (String key:keys) {
            disconnectDB(key);
        }

        if(db_pools.size() > 0)
            db_pools.clear();
        return;
    }

    @Override
    public void onMessageHandle(MessageNotifyData data) {

    }
    private DBComponentManage(){}

    public static DBComponentManage getInstance(){

        if(instance == null){

            synchronized (ComponentManage.class){

                if(instance == null)

                    instance = new DBComponentManage();
            }
        }

        return instance;
    }

    public int connectDB(String key,String dbUrl,String dbname,String dbPass) {

        int state = -1;
        try {

            if(db_pools.containsKey(key) == false) {

                Class.forName(DRIVER);
                Connection conn = DriverManager.getConnection(dbUrl, dbname, dbPass);
                db_pools.put(key, conn);
                state = 0;

            }
        } catch (Exception throwables) {
            state = -2;
            throwables.printStackTrace();
        }finally {
            return state;
        }
    }

    public void disconnectDB(String key)  {

        if(db_pools.containsKey(key))
        {
            try {

                db_pools.get(key).close();
                db_pools.remove(key);

            } catch (SQLException throwables) {

                throwables.printStackTrace();

            }

        }
    }

    public int select(String key,String sql,Map<String,Object> dataModel){

        int state = -1;
        if(db_pools.containsKey(key)){
            try {
                state = -2;
                Statement stmt = db_pools.get(key).createStatement();
                ResultSet rs = stmt.executeQuery(sql);
                List<String> arrs = new ArrayList<>();
                Map<String,List<Object>> selectData = new HashMap<>();
                for (String itemname:dataModel.keySet()) {
                    arrs.add(itemname);
                    selectData.put(itemname,new ArrayList<Object>());
                }

                while(rs.next()){

                    for (String curkey:arrs) {
                        List<Object> itemdata = selectData.get(curkey);
                        Object modelItem = dataModel.get(curkey);

                        if(modelItem.getClass() == String.class) {
                            itemdata.add( rs.getString(curkey));
                        }else if(modelItem.getClass() == Boolean.class){
                            itemdata.add(rs.getBoolean(curkey));
                        }else if(modelItem.getClass() == Double.class){
                            itemdata.add(rs.getDouble(curkey));
                        }else if(modelItem.getClass() == Integer.class){
                            itemdata.add(rs.getInt(curkey));
                        }else if(modelItem.getClass() == Date.class){
                            itemdata.add(rs.getDate(curkey));
                        }else{
                            assert (false);
                        }

                    }
                }
                state = 0;
                MessageNotifyData mnd = new MessageNotifyData();
                mnd.toolName = "Lua";
                mnd.name = "dbselect";
                mnd.obj1 = selectData;
                ComponentManage.getInstance().send(mnd);

            } catch (SQLException throwables) {
                throwables.printStackTrace();
            }
        }
        return state;
    }

    public int otherSql(String key,String sql){

        if(db_pools.containsKey(key) == false) {
            return -1;
        }

        Connection connection = db_pools.get(key);
        try {
            Statement sm = connection.createStatement();
            int ret = sm.executeUpdate(sql);
            sm.close();
            return ret;
        } catch (SQLException throwables) {
            throwables.printStackTrace();
            return -1;
        }

    }


}
