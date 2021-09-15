using gameStart.Tools;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace gameStart.Data
{
    public class LocalDataRootVersionCtrl : localDataBase
    {
        
        public override List<Dictionary<String, object>> getByString(string key1, string value)
        {
            List<Dictionary<String, object>> ret = new List<Dictionary<String, object>>();
            if(data.Count == 0)
            {
                return null;
            }
            foreach (var item in data)
            {
                if(item.Value != null)
                {
                    Dictionary<String, object> item1 = item.Value;
                    if(item1.ContainsKey(key1) == false)
                    {
                        return ret;
                    }
                    if (item1[key1].ToString().Equals(value))
                    {
                        
                        ret.Add(item.Value);
                    }
                }
            }
            return ret;
        }

        public override uint getLoopIntervalSec()
        {
            return 60;
        }

        public override string getName()
        {
            return "startGame";
        }

        public override string getSqlTableName()
        {
            return "startGameWeb";
        }
        public override bool onUpdata(Int64 idx, Dictionary<String, Object> obj)
        {
            String key = idx.ToString();
            if (data.ContainsKey(key) == false)
            {
                data[key] = new Dictionary<String, Object>();
            }
            foreach (var item in obj)
            {
                data[key][item.Key] = item.Value.ToString().TrimEnd();
            }
            return true;
        }
        public override Object onUpdateItem(String key, Object value)
        {
            switch (key)
            {
                case "pageageVersion":
                    return new strVersion(value.ToString());
            }
            return value.ToString().Trim();
        }

    }
}