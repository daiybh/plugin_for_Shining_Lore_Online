using System;
using System.Collections.Generic;
using System.Configuration;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace WindowsFormsApplication1
{
    class GolbalSetting
    {
        private static GolbalSetting _gSettingInstance=null;

        private GolbalSetting()
        {
        }

        public static GolbalSetting GetInstance()
        {
            if(_gSettingInstance==null)
                _gSettingInstance = new GolbalSetting();
            return _gSettingInstance;
        }

        public int step_W;
        public int step_H;
        public  bool [] keyPress_NP = new bool[6];
        public  bool [] keyPress_SP = new bool[6];
        public  bool [] keyPress_HP = new bool[6];

        public void LoadConfig()
        {
            Func<string, string> getConfig = (key) =>
            {
                if (ConfigurationManager.AppSettings[key] != null)
                {
                    return (ConfigurationManager.AppSettings[key]);
                }

                return "";
            };
            try
            {
                step_W = Int32.Parse(getConfig("trackBar_W"));
                step_H = Int32.Parse(getConfig("trackBar_H"));
                for (int i = 0; i < 6; i++)
                {
                    keyPress_NP[i] = Boolean.Parse(getConfig("keyPress_NP" + i.ToString()));
                    keyPress_SP[i] = Boolean.Parse(getConfig("keyPress_SP" + i.ToString()));
                    keyPress_HP[i] = Boolean.Parse(getConfig("keyPress_HP" + i.ToString()));
                }
            }
            catch (System.FormatException)
            {
            }
        }

        public  void savetoConfig()
        {
            Configuration cfa = ConfigurationManager.OpenExeConfiguration(ConfigurationUserLevel.None);
            Func<string,string,bool> gw1 = (key, value) =>{
                cfa.AppSettings.Settings.Remove(key);
                cfa.AppSettings.Settings.Add(key,value);
                return true;
            };
            gw1("trackBar_H", step_H.ToString());
            gw1("trackBar_W", step_W.ToString());
            for (int i = 0; i < 6; i++)
            {
                gw1("keyPress_NP"+i.ToString(), keyPress_NP[i].ToString());
                gw1("keyPress_SP" + i.ToString(), keyPress_SP[i].ToString());
                gw1("keyPress_HP" + i.ToString(), keyPress_HP[i].ToString());
            }
            cfa.Save();
        }

    }
}
