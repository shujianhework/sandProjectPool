using gameStart.Tools;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace gameStart.Data
{
    public class localDataUpdateInfos : localDataBase
    {
        public override List<Dictionary<string, object>> getByString(string key1, string value)
        {
            List<Dictionary<String, object>> ret = new List<Dictionary<String, object>>();
            if (data.Count == 0)
            {
                return null;
            }
            foreach (var item in data)
            {
                if (item.Value != null)
                {
                    Dictionary<String, object> item1 = item.Value;
                    if (item1.ContainsKey(key1) == false)
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
            return 40;
        }

        public override string getName()
        {
            return "updateInfos";
        }

        public override string getSqlTableName()
        {
            return "updateInfos";
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