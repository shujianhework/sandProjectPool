using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace gameStart.Logic
{
    public class LogicBase
    {
        protected delegate bool TestDelegate(bool isDefault, string key, string value);
        protected static bool inputParamHandler(System.Web.UI.Page page,Dictionary<String,String> keys, Func<bool, String, String, bool> func)
        {
            if(keys.Count > 0)
            {
                bool isDefault = false;
                foreach (var item in keys)
                {
                    isDefault = false;
                    String value = page.Request[item.Key];
                    if (value == null)
                    {
                        value = item.Value;
                        isDefault = true;
                    }
                    if (func(isDefault, item.Key, value) == false)
                        return false;
                }
            }
            return true;
        }
        protected static String mapSS2Str(Dictionary<String, String> map)
        {
            string str = "{";
            if (map.Count > 0)
            {
                foreach (var item in map)
                {
                    str = str + "\"" + item.Key + "\":\"" + item.Value + "\",";
                }
                str = str.Substring(0, str.Length - 1);
                return str + "}";
            }
            else
                return "{}";
        }
    }
}