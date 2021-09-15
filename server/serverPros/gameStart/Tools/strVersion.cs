using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace gameStart.Tools
{
    public class strVersion
    {
        private uint numSystem = 0;
        private List<uint> numArrs = new List<uint>();
        static private string char2Value = "0123456789abcdefgtijmnpqrsuvxz";
        private const uint sigMax = 0xffffffff;
        private bool init(String version,uint numberSystem)
        {
            numSystem = 0;
            string[] arr = version.Split('.');
            for (int i = 0; i < arr.Length; i++)
            {
                string str = arr[i];
                uint value = 0;
                for (int j = 0; j < str.Length; j++)
                {
                    char c = str[j];
                    int idx = char2Value.IndexOf(c);
                    if (idx >= 0 && idx < numberSystem)
                    {
                        value = value * numberSystem + (uint)idx;
                        if(value > sigMax)
                        {
                            break;
                        }
                    }
                    else
                        return false;
                }
                numArrs.Add(value);
            }
            numSystem = numberSystem;
            return true;
        }
        public strVersion(String version, uint numberSystem)
        {
            if(numberSystem < 2 || char2Value.Count() <= numberSystem)
            {
                return;
            }
            if (init(version, numberSystem) == false)
                numArrs.Clear();
        }
        public strVersion(String version)
        {
            if (init(version, 10) == false)
                numArrs.Clear();
            
        }
        public override string ToString()
        {
            if (numSystem == 0)
                return "error";
            if (numArrs.Count == 0)
                return "0";
            String str = "";
            for (int i = 0; i < numArrs.Count; i++)
            {
                str = str + numArrs[i] + ".";
            }
            str = str.Substring(0, str.Length - 1);
            return str;
        }
        public static bool operator !=(strVersion v1,strVersion v2)
        {
            return !(v1 == v2);
        }
        public static bool operator ==(strVersion v1, strVersion v2)
        {
            if (v1.numArrs.Count == v2.numArrs.Count)
            {
                for (int i = 0; i < v1.numArrs.Count; i++)
                {
                    if (v1.numArrs[i] != v2.numArrs[i])
                        return false;
                }
                return true;
            }
            return false;
        }
        public static bool operator >=(strVersion v1, strVersion v2)
        {
            if (v1 == v2)
                return true;
            return v1 > v2;
        }
        public static bool operator <=(strVersion v1, strVersion v2)
        {
            if (v1 == v2)
                return true;
            return v1 < v2;
        }
        public static bool operator >(strVersion v1,strVersion v2)
        {
            if (v1 == v2)
                return false;
            int min = Math.Min(v1.numArrs.Count, v2.numArrs.Count);
            for (int i = 0; i < min; i++)
            {
                if (v1.numArrs[i] != v2.numArrs[i])
                    return v1.numArrs[i] > v2.numArrs[i];
            }
            if (min == v1.numArrs.Count)
                return false;
            return true;
        }
        public static bool operator <(strVersion v1, strVersion v2)
        {
            if (v1 == v2)
                return false;
            int min = Math.Min(v1.numArrs.Count, v2.numArrs.Count);
            for (int i = 0; i < min; i++)
            {
                if (v1.numArrs[i] != v2.numArrs[i])
                    return v1.numArrs[i] > v2.numArrs[i];
            }
            if (min == v1.numArrs.Count)
                return false;
            return true;
        }
    }
}