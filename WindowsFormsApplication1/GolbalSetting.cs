using System;
using System.Collections.Generic;
using System.Configuration;
using System.Linq;
using System.Security.Cryptography;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Guagua
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
        public int threadSleep = 5 * 1000;
        public int step_W=17;
        public int step_H=29;
        public  bool [] keyPress_NP = new bool[6] { true, false, false, false, false, true };
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
           
                step_H = Int32.Parse(getConfig("trackBar_H"));
           
                for (int i = 0; i < 6; i++)
                {
                    keyPress_NP[i] = Boolean.Parse(getConfig("keyPress_NP" + i.ToString()));
                    keyPress_SP[i] = Boolean.Parse(getConfig("keyPress_SP" + i.ToString()));
                    keyPress_HP[i] = Boolean.Parse(getConfig("keyPress_HP" + i.ToString()));
                }
                HPPercent = Int32.Parse(getConfig("HPPercent"));
                SPPercent = Int32.Parse(getConfig("SPPercent"));
                NPPercent = Int32.Parse(getConfig("NPPercent"));
                threadSleep = Int32.Parse(getConfig("threadSleep"));
            }
            catch (System.FormatException)
            {
            }
        }
        public void updateConfig(ref ObjectInfo oi)
        {
            string uN = escape(oi.userName);
            CustomSection cs = ConfigurationManager.GetSection(uN) as CustomSection;
            if (cs == null) return;
            oi.bAttack = cs.bAttack;
            oi.bPickUP = cs.bPickUP;
            oi.enableWork = cs.enableWork;

        }

        string escape(string org)
        {
            return "E"+EncryptWithMD5(org);
            string uN = System.Security.SecurityElement.Escape(org);
            uN = uN.Replace("!", "").Replace(" ", "").Replace("！", "");//来这儿！
            return uN;
        }
        public static string EncryptWithMD5(string source)
        {
            byte[] sor = Encoding.UTF8.GetBytes(source);
            MD5 md5 = MD5.Create();
            byte[] result = md5.ComputeHash(sor);
            StringBuilder strbul = new StringBuilder(40);
            for (int i = 0; i < result.Length; i++)
            {
                strbul.Append(result[i].ToString("x2"));//加密结果"x2"结果为32位,"x3"结果为48位,"x4"结果为64位

            }
            return strbul.ToString();
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
                cs.userName = oi.userName;
                string uN = escape(oi.userName);
                cfa.Sections.Remove(uN);
                cfa.Sections.Add(uN, cs);
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
            gw1(("threadSleep"), threadSleep.ToString());

            foreach (var obj in objlist)
            {
                
                //cfa.AppSettings.Settings.Add(obj.userName,);
            }
            cfa.Save();
        }

    }
}
