using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace Guagua
{
    class EnumReportApp
    {

        public delegate bool CallBack(IntPtr hwnd, int lParam);


        [DllImport("user32")]
        private static extern int EnumWindows(CallBack x, int y);

        [DllImport("user32.dll")]
        public static extern void GetWindowText(IntPtr hWnd, StringBuilder lpString, Int32 nMaxCount);

        [DllImport("user32.dll", SetLastError = true, CharSet = CharSet.Auto)]
        static extern int GetWindowTextLength(IntPtr hWnd);

        private long nLoopCnt = 0;
        public bool Report(IntPtr hwnd, int lParam)
        {
            nLoopCnt++;
            Console.WriteLine("{0}>>Window handle is {1},title:{2} ",nLoopCnt,hwnd,GetText(hwnd));
            
            return true;
        }


        public string GetText(IntPtr hwnd)
        {
            int length = GetWindowTextLength(hwnd);
            StringBuilder sb = new StringBuilder(length + 1);
            GetWindowText(hwnd, sb, sb.Capacity);
            return sb.ToString();
        }

        public void doMain()
        {
            CallBack myCallBack = new CallBack(Report);
            EnumWindows(myCallBack, 0);
            Console.ReadLine();
        }
    }
}
