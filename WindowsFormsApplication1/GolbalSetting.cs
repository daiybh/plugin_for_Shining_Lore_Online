using System;
using System.Collections.Generic;
using System.Configuration;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

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
        public int NPPercent = 6;
        public  bool [] keyPress_SP = new bool[6];
        public int SPPercent = 6;
        public  bool [] keyPress_HP = new bool[6];
        public int HPPercent = 6;

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
                if (step_W < 1 || step_W > 100)
                    step_W = 17;
                step_H = Int32.Parse(getConfig("trackBar_H"));
                if (step_H < 1 || step_H > 100)
                    step_H = 29;
                for (int i = 0; i < 6; i++)
                {
                    keyPress_NP[i] = Boolean.Parse(getConfig("keyPress_NP" + i.ToString()));
                    keyPress_SP[i] = Boolean.Parse(getConfig("keyPress_SP" + i.ToString()));
                    keyPress_HP[i] = Boolean.Parse(getConfig("keyPress_HP" + i.ToString()));
                }
                HPPercent = Int32.Parse(getConfig("HPPercent"));
                SPPercent = Int32.Parse(getConfig("SPPercent"));
                NPPercent = Int32.Parse(getConfig("NPPercent"));
            }
            catch (System.FormatException)
            {
            }
        }
        public void updateConfig(ref ObjectInfo oi)
        {
            CustomSection cs = ConfigurationManager.GetSection(oi.userName) as CustomSection;
            if (cs == null) return;
            oi.bAttack = cs.bAttack;
            oi.bPickUP = cs.bPickUP;
            oi.enableWork = cs.enableWork;

        }


        public  void savetoConfig(IList<ObjectInfo> objlist)
        {
            Configuration cfa = ConfigurationManager.OpenExeConfiguration(ConfigurationUserLevel.None);


            foreach (ObjectInfo oi in objlist)
            {
                CustomSection cs = new CustomSection();
                cs.enableWork = oi.enableWork;
                cs.bAttack = oi.bAttack;
                cs.bPickUP = oi.bPickUP;
                cfa.Sections.Remove(oi.userName);
                cfa.Sections.Add(oi.userName, cs);
            }

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

            gw1(("HPPercent"), HPPercent.ToString() );
            gw1(("SPPercent"), SPPercent.ToString());
            gw1(("NPPercent"), NPPercent.ToString());

            foreach (var obj in objlist)
            {
                
                //cfa.AppSettings.Settings.Add(obj.userName,);
            }
            cfa.Save();
        }

    }
}
