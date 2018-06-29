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
            this.enableWork = true;
            this.userName = title.Substring(filterLength);
            this.rt = rt;
            center_X = (rt.Right - rt.Left) / 2;
            center_y = (rt.Bottom - rt.Top) / 2;
            if (rt.Height() < 700)
            {
                Object_H = 163;
                Object_W = 50;
            }

        }

        public override string ToString()
        {
            return string.Format("hWnd:{0} title:{1}", this.hWnd, this.title);
        }

        public void setGraphics(Graphics _g)
        {
            g = _g;
        }
        public string userName { get; set; }
        public bool enableWork
        {
            get { return _enableWork; }
            set
            {
                _enableWork = value;
            }
        }
        
        public bool bAttack { get; set; } = true;
        public bool bPickUP { get; set; } = true;
        private bool _bshowWindow = true;

        public bool bShowWindow
        {
            get { return _bshowWindow;}
            set
            {
                _bshowWindow = value;
                showWindow(value);
            }
        }

        private Graphics g;
        private IntPtr hWnd;
        private string title;
        public int center_X = 0;
        public int center_y = 0;
        public int Object_H = 247;
        public int Object_W = 76;
        public MyFindWindow.RECT rt;
        private bool _enableWork = false;
       

        public void showWindow(bool isShow)
        {
            _bshowWindow = isShow;
         MouseEvent.showWindow(this.hWnd,isShow);
        }
        
        private int offsetX = -100;
        public void attack(int x, int y)
        {
            //  RightAttack(x, y);
            if(bAttack)
                MouseEvent.RightClick(this.hWnd, x-150, y);
            if(bPickUP)
                MouseEvent.LeftClick(this.hWnd, x, y);
            if (bAttack)
                MouseEvent.RightClick(this.hWnd, x + 150, y);

            Thread.Sleep(10);
        }

        private bool bPressAdd = false;
        public void pressAdd()
        {
            if (bPressAdd) return;
            bPressAdd = true;
            //发送键盘按键 +
            for (int i = 0; i < 10; i++)
            {
                MouseEvent.moveMouse(hWnd, center_X + i * 10, center_y + i * 10);
                MouseEvent.pressKey(hWnd, Keys.Add);
                Thread.Sleep(1000);
            }
        }
        public void pressZ()
        {
            MouseEvent.pressKey(hWnd, Keys.Z);
        }

        [DllImport("user32.dll", SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        static extern bool PrintWindow(IntPtr hwnd, IntPtr hDC, uint nFlags);


        private Bitmap bmp = null;
        Graphics memoryGraphics = null;
        private IntPtr dc;
        private int lastUpdateTime = 0;

        public void screenshotting()
        {
            int curTime = System.Environment.TickCount & Int32.MaxValue;
            if (curTime - lastUpdateTime < 2000) return;
            lastUpdateTime = curTime;

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

            int hh = 63;
            int firstLine = this.rt.Height()-96;

            //14,701 33,763
            //52,701 63,763
            //81,701 92,763
            a = (10 - (GolbalSetting.GetInstance().HPPercent + 1))/10.0F;
            Color colorHP = bmp.GetPixel(22, Convert.ToInt32(hh * a + firstLine)); //判断 Color.B 是否为0 


            if (colorHP.B != 0)
            {
                //喝血
                if (GolbalSetting.GetInstance().keyPress_HP[0])
                {
                    for (int i = 0; i < 5; i++)
                    {
                        if (GolbalSetting.GetInstance().keyPress_HP[i + 1])
                        {
                            MouseEvent.pressKey(hWnd, Keys.D1 + i);
                            break;
                        }
                    }
                }

                Console.WriteLine("{0},{1}>>life:{1} ", this.userName, a, colorHP.ToString());
            }

            a = (10 - (GolbalSetting.GetInstance().SPPercent + 1)) / 10.0F;
            Color colorSP = bmp.GetPixel(60, Convert.ToInt32(hh * a + firstLine)); //判断 Color.G 是否为0 


            if (colorSP.G != 0)
            {
                //喝血
                // MouseEvent.pressKey(hWnd, Keys.D0);
                if (GolbalSetting.GetInstance().keyPress_SP[0])
                {
                    for (int i = 0; i < 5; i++)
                    {
                        if (GolbalSetting.GetInstance().keyPress_SP[i + 1])
                        {
                            MouseEvent.pressKey(hWnd, Keys.D1 + i);
                            break;
                        }
                    }
                }

                Console.WriteLine("{0},{1}>>tec:{1} ", this.userName, a, colorSP.ToString());
            }

            a = (10 - (GolbalSetting.GetInstance().NPPercent + 1)) / 10.0F;
            Color colorNP = bmp.GetPixel(88, Convert.ToInt32(hh * a + firstLine)); //判断 Color.B 是否为0
            if (colorNP.B != 0)
            {
                //喝血
                //   MouseEvent.pressKey(hWnd, Keys.D0);
                if (GolbalSetting.GetInstance().keyPress_NP[0])
                {
                    for (int i = 0; i < 5; i++)
                    {
                        if (GolbalSetting.GetInstance().keyPress_NP[i + 1])
                        {
                            MouseEvent.pressKey(hWnd, Keys.D1 + i);
                            break;
                        }
                    }
                }
                Console.WriteLine("{0},{1}>>cPower:{2} ", this.userName,a, colorNP.ToString());
            }


            Console.WriteLine("{3}>>colorHP:{0} colorSP:{1} colorNP:{2}", colorHP.ToString(), colorSP.ToString(), colorNP.ToString(), a);
        }

      
    }
    class MouseEvent
    {
        [DllImport("user32.dll", SetLastError = true)]
        public static extern int SendMessage(IntPtr hWnd, int uMsg, int wParam, int lParam);
        [DllImport("user32.dll")]
        public static extern Keys VkKeyScan(char ch);
        [DllImport("user32.dll")]
        public static extern int MapVirtualKey(int Ucode, uint uMapType);

        [DllImport("user32.dll")]
        public static extern int ShowWindow(IntPtr hWnd, int nCmdShow);

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
        public const int WM_MOUSEMOVE = 0x0200;
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

        public static void showWindow(IntPtr hWnd, bool bShow)
        {
            //   SendMessage(hWnd, WM_SHOWWINDOW, bShow?1:0,0);
            ShowWindow(hWnd, bShow ? 1 : 0);
        }
        public static void moveMouse(IntPtr hWnd, int x, int y)
        {
            SendMessage(hWnd, WM_MOUSEMOVE, 0, MakeDWord(x, y));
        }
        public static void pressKey(IntPtr hWnd, Keys key)
        {

            int lParam = 1;
            lParam += MapVirtualKey(key.GetHashCode(), 0) << 16;
            //2883585
            SendMessage(hWnd, WM_KEYDOWN, key.GetHashCode(), lParam);//Thread.Sleep(100);
            lParam += 1 << 30;
            lParam += 1 << 31;
            SendMessage(hWnd, WM_KEYUP, key.GetHashCode(), lParam);//up
        }
        public static void LeftClick(IntPtr hWnd, int x, int y)
        {
            send_message(hWnd, MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 2, x, y);
        }
        public static void RightClick(IntPtr hWnd, int x, int y)
        {
            send_message(hWnd, MOUSEEVENTF_RIGHTUP | MOUSEEVENTF_RIGHTDOWN, 1, x, y);
        }
        public static void send_message(IntPtr hWnd, int dwFlags, int cButtons, int x, int y)
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
