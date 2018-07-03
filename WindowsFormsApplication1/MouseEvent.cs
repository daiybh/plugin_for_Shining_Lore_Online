using System;
using System.Runtime.InteropServices;
using System.Windows.Forms;

namespace Guagua
{
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