using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Threading;
using System.Web;

namespace gameStart.Tools
{
    public enum LogLevels
    {
        Log,
        Info,
        Error,
    }
    public class Log
    {
        static String rootPath;
        static LogLevels writeLevelMin;
        static List<String> logs1 = new List<string>();
        static List<String> logs2 = new List<string>();
        static String shortName = null;
        static DateTime fileDt;
        private static void onLoop()
        {
            while (true)
            {
                if((logs1.Count + logs2.Count) == 0)
                {
                    Thread.Sleep(2);
                }
                else
                {
                    if(logs1.Count > 0)
                    {
                        lock (logs1)
                        {
                            FileStream file = File.Open(rootPath + "/" + shortName, FileMode.Append);
                            foreach (var item in logs1)
                            {
                                byte[] bytes = System.Text.Encoding.UTF8.GetBytes(item+"\n");
                                file.Write(bytes,0,bytes.Length);
                            }
                            file.Flush();
                            file.Close();
                            logs1.Clear();
                        }
                    }
                    if(logs2.Count > 0)
                    {
                        lock (logs2)
                        {

                            FileStream file = File.Open(rootPath + "/" + shortName, FileMode.Append);
                            foreach (var item in logs2)
                            {
                                byte[] bytes = System.Text.Encoding.UTF8.GetBytes(item+"\n");
                                file.Write(bytes, 0, bytes.Length);
                            }
                            file.Flush();
                            file.Close();
                            logs2.Clear();
                        }
                    }
                }
            }
        }
        static Log()
        {
            String path = HttpRuntime.AppDomainAppPath;
            if(Directory.Exists(path+"/logs") == false)
            {
                Directory.CreateDirectory(path + "/logs");
            }

            rootPath = path + "/logs";
            fileDt = DateTime.Now;
            shortName = fileDt.ToString("MM-dd-yyyy")+".log";
            if(File.Exists(rootPath+"/"+shortName) == false)
            {
                FileStream fs = File.Create(rootPath + "/" + shortName);
                fs.Close();
            }
            writeLevelMin = LogLevels.Log;
            Thread thred = new Thread(onLoop);
            thred.Start();
        }
        static public bool write(LogLevels ll,String pageName,String LogId, String info)
        {
            if (LogId == "")
                LogId = "--not";
            if (pageName == "")
                pageName = "null";
            
            if(ll < writeLevelMin)
                return false;

            DateTime dt = DateTime.Now;
            String text= dt.ToString("[[dd-MM-yyyy_hh-mm-ss ");
            text = text + pageName + " " + LogId;
            switch (ll)
            {
                case LogLevels.Log:
                    text = text + " L]]";
                    break;
                case LogLevels.Info:
                    text = text + " I]]";
                    break;
                case LogLevels.Error:
                    text = text + " E]]";
                    break;
                default:
                    text = text + " O]]";
                    break;
            }
            text = text + "::" + info;
            String shortName1 = dt.ToString("MM-dd-yyyy")+".log";
            bool swapFileName = false;
            if(shortName != shortName1)
            {
                if (File.Exists(rootPath + "/" + shortName1) == false)
                {
                    FileStream fs = File.Create(rootPath + "/" + shortName1);
                    fs.Close();
                }
                swapFileName = true;
            }

            if(logs1.Count == 0)
            {
                lock (logs1)
                {
                    logs1.Add(text);
                    text = "";
                }
            }
            else { 
                lock (logs2)
                {
                    logs2.Add(text);
                    text = "";
                }
            }
            if (swapFileName)
            {
                shortName = shortName1;
            }
            return true;
        }
        
    }
}