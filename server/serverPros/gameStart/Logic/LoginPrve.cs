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

        public static void startGame(System.Web.UI.Page page)
        {
            String pagename = page.GetType().Name;
            String tryHashValue = "";

            Dictionary<String, String> inputParamKeys = new Dictionary<string, string>();
            inputParamKeys["channeId"] = "";
            inputParamKeys["packageName"] = "";
            inputParamKeys["pageageVersion"] = "";
            inputParamKeys["clienLogicId"] = "";
            
            Dictionary<String, String> inputParams = new Dictionary<string, string>();
            Dictionary<String, String> map = new Dictionary<string, string>();

            Func<bool,String,String,bool> func = (bool isDefault, String key, String value)=>{
                if( ( isDefault == false || !key.Equals("clienLogicId")) && value.Length > 0)
                {
                    inputParams[key] = value;
                    if (key.Equals("clienLogicId"))
                    {
                        tryHashValue = value;
                    }
                    return true;
                }
                map["code"] = "201";
                
                Log.write(LogLevels.Info, pagename, tryHashValue, "check paramerror :: " + key);
                map["value"] = "check paramerror :: "+key;
                return false;
            };
            if (inputParamHandler(page,inputParamKeys, func) == false)
            {
                page.Response.Write(mapSS2Str(map));
                return ;
            }
            String channeId = inputParams["channeId"];
            String packageName = inputParams["packageName"];
            String pageageVersion = inputParams["pageageVersion"];

            if(tryHashValue == null || tryHashValue.Equals(""))
            {
                tryHashValue = channeId + DateTime.Now.ToString("ss_MM_mm_dd_HH") + LocalDataManages.random.Next(1, 0xffff23f);
            }
            Log.write(LogLevels.Info, pagename, tryHashValue, "must params:: channeId = " + channeId + " packageName = " + packageName + " pageageVersion = " + pageageVersion);
            map["Logid"] = tryHashValue;

            List<Dictionary<String, object>> list = LocalDataManages.getByString("startGame", "channeId", channeId);
            if (list == null || list.Count == 0)
            {
                map["code"] = list == null ? "401" : "402";
                Log.write(LogLevels.Info, pagename, tryHashValue, "pageageVersion = null");
                map["value"] = "pageageVersion = null";
                page.Response.Write(mapSS2Str(map));
                return;
            }

            map["code"] = "202";
            Dictionary<String, Object> item2 = null;
            strVersion inputVersion = new strVersion(pageageVersion);
            List<Dictionary<String, Object>> item3 = new List<Dictionary<string, Object>>();
            foreach (var item in list)
            {
                Dictionary<String, Object> item1 = item;
                if (packageName.Equals(item1["packageName"]))
                {
                    item3.Add(item1);
                    strVersion dbVersion = (strVersion) item1["pageageVersion"];
                    if(dbVersion >= inputVersion)
                    {
                        item2 = item1;
                        break;
                    }
                }
            }
            if (item2 == null)
            {
                map["code"] = "203";
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


        internal static void hotInfos(System.Web.UI.Page page)
        {
            String pagename = page.GetType().Name;
            String tryHashValue = "";

            Dictionary<String, String> inputParamKeys = new Dictionary<string, string>();
            inputParamKeys["channeId"] = "";
            inputParamKeys["packageName"] = "";
            inputParamKeys["pageageVersion"] = "";
            inputParamKeys["Logid"] = "";

            Dictionary<String, String> inputParams = new Dictionary<string, string>();
            Dictionary<String, String> map = new Dictionary<string, string>();

            Func<bool, String, String, bool> func = (bool isDefault, String key, String value) => {
                if (isDefault == false && value.Length > 0)
                {
                    inputParams[key] = value;
                    if (key.Equals("Logid"))
                    {
                        tryHashValue = value;
                    }
                    return true;
                }
                map["code"] = "201";

                Log.write(LogLevels.Info, pagename, tryHashValue, "check paramerror :: " + key);
                map["value"] = "check paramerror :: " + key;
                return false;
            };
            if (inputParamHandler(page, inputParamKeys, func) == false)
            {
                page.Response.Write(mapSS2Str(map));
                return;
            }
            String channeId = inputParams["channeId"];
            String packageName = inputParams["packageName"];
            String pageageVersion = inputParams["pageageVersion"];
            List<Dictionary<String, object>> list = LocalDataManages.getByString("updateInfos", "channeId", channeId);
            if (list == null || list.Count == 0)
            {
                map["code"] = list == null ? "401" : "402";
                Log.write(LogLevels.Info, pagename, tryHashValue, "pageageVersion = null");
                map["value"] = "pageageVersion = null";
                page.Response.Write(mapSS2Str(map));
                return;
            }
            strVersion version = new strVersion(pageageVersion);
            Dictionary<String, object> item2 = null;
            foreach (var item in list)
            {
                Dictionary<String, Object> item1 = item;
                if (packageName.Equals(item1["packageName"]))
                {
                    strVersion dbVersion = (strVersion)item1["pageageVersion"];
                    if(dbVersion >= version)
                    {
                        item2 = item1;
                        break;
                    }
                }
            }
            if (item2 == null)
            {
                map["code"] = "203";
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
    }
}