using gameStart.Tools;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace gameStart.Pages
{
    public partial class test : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            String str1 = Request["v1"];
            String str2 = Request["v2"];
            String base1 = Request["base"];
            String oper = Request["oper"];
            int num = 10;
            if(base1 != null)
            {
                if (int.TryParse(base1,out num) == false)
                    num = 10;
            }
            if (str1 == null)
            {
                Response.Write("error");
                return;
            }
            strVersion version1 = new strVersion(str1, (uint)num);
            if(str2 == null)
            {
                Response.Write(version1.ToString());
                return;
            }
            strVersion version2 = new strVersion(str2, (uint)num);
            if (oper == null)
            {
                Response.Write(version1.ToString()+"   "+version2.ToString());
                return;
            }
            switch (oper)
            {
                case "==":
                    Response.Write(version1.ToString() + "   " + version2.ToString()+ "   " + (version1 == version2));
                    break;
                case "<":
                    Response.Write(version1.ToString() + "   " + version2.ToString() + "   " + (version1 < version2));
                    break;
                case ">":
                    Response.Write(version1.ToString() + "   " + version2.ToString() + "   " + (version1 > version2));
                    break;
                case "!=":
                    Response.Write(version1.ToString() + "   " + version2.ToString() + "   " + (version1 != version2));
                    break;
                case ">=":
                    Response.Write(version1.ToString() + "   " + version2.ToString() + "   " + (version1 >= version2));
                    break;
                case "<=":
                    Response.Write(version1.ToString() + "   " + version2.ToString() + "   " + (version1 <= version2));
                    break;
                //default:
                //    Response.Write(version1.ToString() + "   " + version2.ToString());
            }
        }
    }
}