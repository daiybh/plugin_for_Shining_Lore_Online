﻿using System;
using System.Drawing;
using System.Runtime.InteropServices;
using System.Threading;
using System.Windows.Forms;

namespace WindowsFormsApplication1
{
    class ObjectInfo
    {
       
        public static string filterName = " 永恒天使 - ";
        public static int filterLength = filterName.Length;
        public ObjectInfo(IntPtr _hwnd, string title, MyFindWindow.RECT rt)
        {
            this.hWnd = _hwnd;
            this.title = title;
            this.userName = title.Substring(filterLength);
            this.rt = rt;
            center_X = (rt.Right - rt.Left) / 2;
            center_y = (rt.Bottom - rt.Top) / 2;

        }

        public override string ToString()
        {
            return string.Format("hWnd:{0} title:{1}", this.hWnd, this.title);
        }

        private Thread t1 = null;
        public void startWork()
        {
            t1 = new Thread(new ThreadStart(captureObj));
            t1.IsBackground = true;
            t1.Start();
        }

        public void stopWork()
        {
            bExit = true;
            if (t1!=null && t1.IsAlive)
                t1.Abort();
        }

        public Graphics g { get; set; }
        public IntPtr hWnd { get; set; }
        public string title { get; set; }
        public string userName { get; set; }
        public int center_X = 0;
        public int center_y = 0;
        public int Object_H = 247;
        public MyFindWindow.RECT rt;
        
        public void showWindow(bool isShow)
        {
            MouseEvent.SendMessage(hWnd, MouseEvent.WM_SYSCOMMAND, isShow?MouseEvent.SC_MINIMIZE: MouseEvent.SC_RESTORE, 0);
        }
        ManualResetEvent autoEvent = new ManualResetEvent(true);
        private bool bPause = false;
        internal void pauseWork()
        {
            if(bPause)
                autoEvent.Set();
            else
                autoEvent.Reset();
            bPause = !bPause;
        }
        

        public void attack(int x, int y)
        {
            MouseEvent.LeftClick(this.hWnd,x,y);
             
            MouseEvent.RightClick(this.hWnd,x,y);
            Thread.Sleep(10);
        }

        private bool bExit = false;

        public void captureObj()
        {
            int X = 0;
            int Y = 0;

            //发送键盘按键 +
            for (int i = 0; i < 10; i++)
            {
                    MouseEvent.pressKey(hWnd, Keys.Add);
                Thread.Sleep(1000);
            }
            Thread.Sleep(100);
            while (!bExit)
            {
                pressZ();
                for (int h = Object_H * -1; h < 10; h += GolbalSetting.GetInstance().step_H)
                {
                    for (int w = -45; w < 30; w += GolbalSetting.GetInstance().step_W)
                    {
                        X = center_X + w;
                        Y = center_y + h;
                        attack(X, Y);
                        autoEvent.WaitOne();
                    }
                }

            }
        }
        public void pressZ()
        {
            MouseEvent.pressKey(hWnd,Keys.Z);
        }
        [DllImport("user32.dll", SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        static extern bool PrintWindow(IntPtr hwnd, IntPtr hDC, uint nFlags);


        private Bitmap bmp = null;
        Graphics memoryGraphics = null;
        private IntPtr dc ;
        public void screenshotting()
        {
            if (bmp == null)
            {
                bmp = new Bitmap(this.rt.Width(), this.rt.Height(), g);
                memoryGraphics = Graphics.FromImage(bmp);
              //  dc = memoryGraphics.GetHdc();
            }

            dc = memoryGraphics.GetHdc();
            bool success = PrintWindow(this.hWnd, dc, 0);
            memoryGraphics.ReleaseHdc(dc);
            // bmp now contains the screenshot
            bmp.Save("c:\\jpeg\\ccccc.jpg");
            float a = 0.6F;

            int hh = 763 - 701;
            int pos = Convert.ToInt32(hh * (1 - a) + 701);

            //14,701 33,763
            //52,701 63,763
            //81,701 92,763
            Color cLife = bmp.GetPixel(22, pos);//判断 Color.B 是否为0 
            Color ctec = bmp.GetPixel(60, pos);//判断 Color.G 是否为0 
            Color cPower = bmp.GetPixel(88, pos);//判断 Color.B 是否为0

            if (cLife.B != 0)
            {
                //喝血
                MouseEvent.pressKey(hWnd, Keys.D1);
            }
            if (ctec.B == 0)
            {
                //喝血
               // MouseEvent.pressKey(hWnd, Keys.D0);
            }
            if (cPower.B == 0)
            {
                //喝血
             //   MouseEvent.pressKey(hWnd, Keys.D0);
            }
            Console.WriteLine("{3}>>life:{0} tec:{1} power:{2}", cLife.ToString(), ctec.ToString(), cPower.ToString(), pos);
        }
        class MouseEvent
        {
            [DllImport("user32.dll", SetLastError = true)]
            public static extern int SendMessage(IntPtr hWnd, int uMsg, int wParam, int lParam);
            [DllImport("user32.dll")]
            public static extern Keys VkKeyScan(char ch);
            [DllImport("user32.dll")]
            public static extern int MapVirtualKey(int Ucode, uint uMapType);

            public const int WM_SHOWWINDOW = 0x0018;
            public const int WM_SYSCOMMAND = 0x0112;
            public const int SC_MINIMIZE = 0xF020;
            public const int SC_RESTORE = 0xF120;
            public const int WM_LBUTTONDOWN = 513; // 鼠标左键按下 
            public const int WM_LBUTTONUP = 514; // 鼠标左键抬起 
            public const int WM_RBUTTONDOWN = 516; // 鼠标右键按下 
            public const int WM_RBUTTONUP = 517; // 鼠标右键抬起 
            public const int WM_MBUTTONDOWN = 519; // 鼠标中键按下 
            public const int WM_MBUTTONUP = 520; // 鼠标中键抬起 
            public const int MOUSEEVENTF_MOVE = 0x0001; // 移动鼠标   
            public const int MOUSEEVENTF_LEFTDOWN = 0x0002; // 鼠标左键按下  
            public const int MOUSEEVENTF_LEFTUP = 0x0004; // 鼠标左键抬起  
            public const int MOUSEEVENTF_RIGHTDOWN = 0x0008; // 鼠标右键按下  
            public const int MOUSEEVENTF_RIGHTUP = 0x0010; // 鼠标右键抬起   
            public const int MOUSEEVENTF_MIDDLEDOWN = 0x0020; // 鼠标中键按下 
            public const int MOUSEEVENTF_MIDDLEUP = 0x0040; // 鼠标中键抬起   
            public const int MOUSEEVENTF_ABSOLUTE = 0x8000; // 绝对坐标 
            public const int WM_KEYDOWN = 0x100;
            public const int WM_KEYUP = 0x101;
            public const int WM_CHAR = 0x0102;

            public static void pressKey(IntPtr hWnd,Keys key)
            {

                int lParam = 1;
                lParam += MapVirtualKey(key.GetHashCode(), 0) << 16;
                //2883585
                SendMessage(hWnd, WM_KEYDOWN, key.GetHashCode(), lParam);//Thread.Sleep(100);
                lParam += 1 << 30;
                lParam += 1 << 31;
                SendMessage(hWnd, WM_KEYUP, key.GetHashCode(), lParam);//up
            }
            public static void LeftClick(IntPtr hWnd,int x, int y)
            {
                send_message(hWnd, MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 2, x, y);
            }
            public static void RightClick(IntPtr hWnd, int x, int y)
            {
                send_message(hWnd, MOUSEEVENTF_RIGHTUP | MOUSEEVENTF_RIGHTDOWN, 1, x, y);
            }
            public   static void send_message(IntPtr hWnd, int dwFlags, int cButtons, int x, int y)
            {
                if ((dwFlags | MOUSEEVENTF_LEFTDOWN) == dwFlags)
                    SendMessage(hWnd, WM_LBUTTONDOWN, cButtons, MakeDWord(x, y));
                if ((dwFlags | MOUSEEVENTF_LEFTUP) == dwFlags)
                    SendMessage(hWnd, WM_LBUTTONUP, cButtons, MakeDWord(x, y));
                if ((dwFlags | MOUSEEVENTF_RIGHTDOWN) == dwFlags)
                    SendMessage(hWnd, WM_RBUTTONDOWN, cButtons, MakeDWord(x, y));
                if ((dwFlags | MOUSEEVENTF_RIGHTUP) == dwFlags)
                    SendMessage(hWnd, WM_RBUTTONUP, cButtons, MakeDWord(x, y));
                if ((dwFlags | MOUSEEVENTF_MIDDLEDOWN) == dwFlags)
                    SendMessage(hWnd, WM_MBUTTONDOWN, cButtons, MakeDWord(x, y));
                if ((dwFlags | MOUSEEVENTF_MIDDLEUP) == dwFlags)
                    SendMessage(hWnd, WM_MBUTTONUP, cButtons, MakeDWord(x, y));
            }
            static int MakeDWord(int low, int high)
            {
                return low + (high * Abs(~ushort.MaxValue));
            }
            static int Abs(int value)
            {
                return ((value >> 31) ^ value) - (value >> 31);
            }
        }

    }
}