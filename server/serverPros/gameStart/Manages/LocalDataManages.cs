using gameStart.Data;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading;
using System.Web;

namespace gameStart.Manages
{
    //本地数据管理器，这里的数据是惰性加载，并且非实时更新。用作基本返回数据一样，变化数据允许先错误后正确
    //定时刷新
    //只允许查询，不允许在web这里修改或删除的
    public class LocalDataManages
    {
        static private Dictionary<String, localDataBase> dataPools = null;
        static public Random random = new Random();
        public static Int64 getTimeStamp()
        {
            TimeSpan ts = DateTime.UtcNow - new DateTime(1970, 1, 1, 0, 0, 0, 0);
            return Convert.ToInt64(ts.TotalSeconds);
        }
        static private void run()
        {
            Dictionary<String, uint> tempvalues = new Dictionary<string, uint>();
            Int64 dt = getTimeStamp();
            while (true)
            {
                if(dataPools.Count > 0)
                {
                    if(tempvalues.Count != dataPools.Count)
                    {
                        foreach (var item in dataPools)
                        {
                            if(tempvalues.ContainsKey(item.Key) == false)
                            {
                                tempvalues[item.Key] =  item.Value.getLoopIntervalSec() + 1;
                                item.Value.init();
                            }
                        }
                    }
                    Int64 dt1 = getTimeStamp();
                    if (dt1 > dt)
                    {
                        foreach (var item in dataPools)
                        {
                            if (tempvalues.ContainsKey(item.Key))
                            {
                                uint sec = tempvalues[item.Key];
                                int dt2 = (int)(dt1 - dt);
                                if (sec > dt2 && dt2 >= 0)
                                {
                                    sec = (uint)(sec - dt2);
                                }
                                else
                                {
                                    sec = 0;
                                }
                                if (sec < 2)
                                {
                                    tempvalues[item.Key] = item.Value.getLoopIntervalSec() + 1;
                                    item.Value.updata();
                                }
                                else
                                {
                                    tempvalues[item.Key] = sec;
                                }
                            }
                        }
                        dt = dt1;
                    }
                    Thread.Sleep(270);
                }
                else
                {
                    Thread.Sleep(300);
                }
            }
        }
        static public bool addLocalDataBase(localDataBase ldb)
        {
            String key = ldb.getName();
            if (dataPools.ContainsKey(key))
                return false;
            dataPools[key] = ldb;
            return true;
            
        }
        static LocalDataManages()
        {
            Thread thread = new Thread(LocalDataManages.run);
            thread.Start();
            dataPools = new Dictionary<string, localDataBase>();
        }
        static public List<Dictionary<String, object>> getByString(String dataName,String key1,String value)
        {
            List<Dictionary<String, object>> ret = new List<Dictionary<String, object>>();
            if (dataPools.ContainsKey(dataName) == false)
                return null;
            ret = dataPools[dataName].getByString(key1, value);
            return ret;
        }
    }
}