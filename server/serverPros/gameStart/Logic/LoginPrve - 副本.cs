using gameStart.Data;
using gameStart.Manages;
using gameStart.Pages;
using gameStart.Tools;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace gameStart.Logic
{
    public class LoginPrve: LogicBase
    {
        static LoginPrve() {
            LocalDataManages.addLocalDataBase(new LocalDataRootVersionCtrl());
        }
        public static String mapSS2Str(Dictionary<String,String> map)
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


        public static void startGame(System.Web.UI.Page page)
        {

            String channeId = page.Request["channeId"];
            String packageName = page.Request["packageName"];
            String pageageVersion = page.Request["pageageVersion"];
            String tryHashValue = page.Request["clienLogicId"];
            String pagename = page.GetType().Name;
            Dictionary<String, String> map = new Dictionary<string, string>();
            
            map["code"] = "1";
            if (channeId == null || channeId.Equals(""))
            {
                Log.write(LogLevels.Info, pagename, "", "channeId = null");
                map["value"] = "channeId = null";
                page.Response.Write(mapSS2Str(map));
                return;
            }

            map["code"] = "2";
            if (packageName == null || packageName.Equals(""))
            {
                Log.write(LogLevels.Info, pagename, "", "packageName = null");
                map["value"] = "packageName = null";
                page.Response.Write(mapSS2Str(map));
                return;
            }

            map["code"] = "3";
            if (pageageVersion == null || pageageVersion.Equals(""))
            {
                Log.write(LogLevels.Info, pagename, "", "pageageVersion = null");
                map["value"] = "pageageVersion = null";
                page.Response.Write(mapSS2Str(map));
                return;
            }
            if(tryHashValue == null || tryHashValue.Equals(""))
            {
                tryHashValue = channeId + DateTime.Now.ToString("ss_MM_mm_dd_HH") + LocalDataManages.random.Next(1, 0xffff23f);
            }
            Log.write(LogLevels.Info, pagename, tryHashValue, "must params:: channeId = " + channeId + " packageName = " + packageName + " pageageVersion = " + pageageVersion);
            map["Logid"] = tryHashValue;
            List<Dictionary<String, object>> list = LocalDataManages.getByString("startGame", "channeId", channeId);
            if (list.Count == 0)
            {
                map["code"] = "401";
                Log.write(LogLevels.Info, pagename, tryHashValue, "pageageVersion = null");
                map["value"] = "pageageVersion = null";
                page.Response.Write(mapSS2Str(map));
                return;
            }

            map["code"] = "5";
            Dictionary<String, Object> item2 = null;
            if (packageName.Equals("test"))
            {
                item2 = (Dictionary<String, Object>)list[0];
            }
            else
            {
                List<Dictionary<String, Object>> item3 = new List<Dictionary<string, Object>>();
                foreach (var item in list)
                {
                    Dictionary<String, Object> item1 = item;
                    if (packageName.Equals(item1["packageName"]))
                    {
                        item3.Add(item1);
                        if (pageageVersion.Equals(item1["pageageVersion"]))
                        {
                            item2 = item1;
                            break;
                        }
                    }
                }
                if(item2 == null && item3.Count > 0)
                {
                    String[] versiona = pageageVersion.Split('.');
                    foreach (var item in item3)
                    {
                        String version = item["pageageVersion"].ToString();
                        String[] versionb = version.Split('.');
                        
                        int valuea = 0;
                        int valueb = 0;
                        if (versiona.Length >= versionb.Length)
                        {
                            //3.5.1  3.5 false 3.6 true
                            for (int i = 0; i < versionb.Length; i++)
                            {
                                if(int.TryParse(versiona[i],out valuea) && int.TryParse(versionb[i],out valueb))
                                {
                                    if(valuea != valueb)
                                    {
                                        if(valuea < valueb)
                                        {
                                            item2 = item;
                                        }
                                        break;
                                    }
                                }
                                else
                                {
                                    Log.write(LogLevels.Info, pagename, tryHashValue, "pageageVersion 2 int error");
                                    map["value"] = "pageageVersion 2 int error";
                                    page.Response.Write(mapSS2Str(map));
                                    return;
                                }
                            }
                        }
                        else
                        {
                            //3.6  3.5.1 false 3.2.1 true
                            for (int i = 0; i < versiona.Length; i++)
                            {
                                if (int.TryParse(versiona[i], out valuea) && int.TryParse(versionb[i], out valueb))
                                {
                                    if (valuea != valueb)
                                    {
                                        if (valuea < valueb)
                                        {
                                            item2 = item;
                                        }
                                        break;
                                    }else if(i == (versiona.Length - 1))
                                    {
                                        item2 = item;
                                    }
                                }
                                else
                                {
                                    Log.write(LogLevels.Info, pagename, tryHashValue, "pageageVersion 2 int error");
                                    map["value"] = "pageageVersion 2 int error";
                                    page.Response.Write(mapSS2Str(map));
                                    return;
                                }
                            }
                        }
                        
                    }
                }
                //传入2.0.1 记录 3.0.1 4.0.1 5.0.1 >>>
            }
            if(item2 == null)
            {
                map["code"] = "6";
                Log.write(LogLevels.Info, pagename, tryHashValue, "pageageVersion 2 not match version");
                map["value"] = "pageageVersion 2 not match version";
                page.Response.Write(mapSS2Str(map));
                return;
            }
            else
            {
                map["code"] = "0";
                map["urls"] = item2["urls"].ToString();
                map["value"] = "ok";
                page.Response.Write(mapSS2Str(map));
                return;
            }
        }

        internal static void hotInfos(System.Web.UI.Page hotInfos)
        {
        }
    }
}