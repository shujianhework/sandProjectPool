using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using gameStart.Tools;
namespace gameStart.Pages
{
    public partial class startGame : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            try
            {
                Log.write(LogLevels.Log, this.GetType().Name, "", "Page_Load 1");
                Logic.LoginPrve.startGame(this);
                Log.write(LogLevels.Log, this.GetType().Name, "", "Page_Load 2");
            }
            catch(Exception ex)
            {
                Log.write(LogLevels.Error, this.GetType().Name, "", ex.ToString());
            }
        }
    }
}