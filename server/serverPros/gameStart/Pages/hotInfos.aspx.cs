using gameStart.Tools;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace gameStart.Pages
{
    public partial class hotInfos : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            try
            {
                Log.write(LogLevels.Log, this.GetType().Name, "", "Page_Load 1");
                Logic.LoginPrve.hotInfos(this);
                Log.write(LogLevels.Log, this.GetType().Name, "", "Page_Load 2");
            }
            catch (Exception ex)
            {
                Log.write(LogLevels.Error, this.GetType().Name, "", ex.ToString());
            }
        }
    }
}