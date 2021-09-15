using System;
using System.Collections.Generic;
using System.Configuration;
using System.Linq;
using System.Web;

namespace gameStart.Manages
{
    public class ConfigManage
    {
        private static Dictionary<String, String> configs = new Dictionary<string, string>();
        public static String get(String key,String defaultStr)
        {
            if (configs.ContainsKey(key) == false)
                return defaultStr;
            ConnectionStringSettings value = System.Web.Configuration.WebConfigurationManager.ConnectionStrings[key];
            if(value != null )
            {
                configs[key] = value.ToString();
                return value.ToString();
            }
            return configs[key];
        }
        public static void set(String key,String value)
        {
            configs[key] = value;
        }
    }
}