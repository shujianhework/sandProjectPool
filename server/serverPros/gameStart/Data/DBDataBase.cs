using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace gameStart.Data
{
    public abstract class DBDataBase
    {
        public abstract bool clear();
        public abstract bool onUpdata(Int64 idx, Dictionary<String, Object> obj);
        public abstract bool updataEnd();
    }
}