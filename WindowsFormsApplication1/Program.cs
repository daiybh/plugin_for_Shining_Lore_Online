﻿using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Guagua
{
   
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main(string[]args)
        {
            if (args.Length > 0)
            {
              //  NativeMethods.AllocConsole();
             //   Console.WriteLine("kaishi....");

             /*   ObjecInfo_HP_SP_NP objMem1 = new ObjecInfo_HP_SP_NP(0x8f68);
                ObjecInfo_HP_SP_NP objMem2 = new ObjecInfo_HP_SP_NP(32752);

                while (true)
                {
                    objMem1.doRead();
                    objMem2.doRead();
                    Thread.Sleep(500);
                }/**/

            }
            GolbalSetting.GetInstance().LoadConfig();
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new Form2());
        }
    }
}

