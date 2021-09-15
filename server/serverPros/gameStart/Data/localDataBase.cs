using gameStart.Manages;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace gameStart.Data
{
    public abstract class localDataBase: DBDataBase
    {
        protected String dbconnect = "";
        protected Dictionary<String, Dictionary<String,Object>> data = new Dictionary<string, Dictionary<String, Object>>();
        protected Dictionary<String, Dictionary<String, Object>> dbdata = new Dictionary<string, Dictionary<String, Object>>();
        public localDataBase()
        {
            dbconnect = ConfigManage.get("connectSqlServer", "Data Source=47.75.78.46;Initial Catalog=ST2006DB;Persist Security Info=True;User ID=sa;Password=SQL@sa46;Database=ctrlBrid");
        }
        public bool isEmpty()
        {
            return data.Count == 0;
        }
        //频率 ，每隔n秒执行一次db更新
        public abstract uint getLoopIntervalSec();
        public abstract String getSqlTableName ();
        //返回的是 key名为key1 并且他的之为value的是数据集合数组
        public abstract List<Dictionary<String, object>> getByString(String key1,String value);
        public abstract String getName();
        public bool init()
        {
            updata();
            return true;
        }
        public bool updata()
        {
            String tableName = getSqlTableName();
            String sqlcmd = "select * from " + tableName;
            return DBManage.Select(dbconnect, sqlcmd, this);
        }
        public override bool clear()
        {
            dbdata.Clear();
            return true;
        }
        public abstract Object onUpdateItem(String key, Object value);
        public override bool onUpdata(Int64 idx, Dictionary<String, Object> obj)
        {
            String key = idx.ToString();
            if(dbdata.ContainsKey(key) == false)
            {
                dbdata[key] = new Dictionary<String, Object>();
            }
            foreach (var item in obj)
            {
                dbdata[key][item.Key] = onUpdateItem(key,item.Value);
            }
            return true;
        }
        public override bool updataEnd()
        {
            lock (this)
            {
                data = dbdata;
                dbdata = new Dictionary<string, Dictionary<string, object>>();
            }
            return true;
        }
    }
}