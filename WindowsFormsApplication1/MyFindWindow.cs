using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;
using System.Windows.Forms;
using static Guagua.MyFindWindow;
using static Guagua.FindObjectInfo;

namespace Guagua
{
    class MyFindWindow
    {
        [DllImport("user32")]
        [return: MarshalAs(UnmanagedType.Bool)]
        //IMPORTANT : LPARAM  must be a pointer (InterPtr) in VS2005, otherwise an exception will be thrown
        private static extern bool EnumChildWindows(IntPtr window, EnumWindowProc callback, IntPtr i);

        //the callback function for the EnumChildWindows

        [DllImport("user32.dll", CharSet = CharSet.Auto, SetLastError = true)]
        public static extern int GetWindowThreadProcessId(IntPtr handle, out int processId);

        [DllImport("User32.dll")]
        public static extern int GetWindowText(IntPtr WinHandle, StringBuilder Title, int size);
        [DllImport("user32.dll")]
        public static extern int GetClassName(IntPtr WinHandle, StringBuilder Type, int size);
        [DllImport("user32.dll")]
        public static extern bool GetWindowRect(IntPtr hwnd, ref RECT rectangle);

        /// <summary>
        /// 查找窗体
        /// </summary>
        /// <param name="lpClassName">窗体的类名称，比如Form、Window。若不知道，指定为null即可</param>
        /// <param name="lpWindowName">窗体的标题/文字</param>
        /// <returns></returns>
        [DllImport("user32.dll", EntryPoint = "FindWindow", SetLastError = true)]
        private static extern IntPtr FindWindow(string lpClassName, string lpWindowName);
        /// <summary>
        /// 查找子窗体（控件）
        /// </summary>
        /// <param name="hwndParent">父窗体句柄，不知道窗体时可指定IntPtr.Zero</param>
        /// <param name="hwndChildAfter">子窗体(控件)，通常不知道子窗体(句柄)，指定0即可</param>
        /// <param name="lpszClass">子窗体(控件)的类名，通常指定null，它是window class name，并不等同于C#中的列名Button、Image、PictureBox等，两者并不相同，可通过GetClassName获取正确的类型名</param>
        /// <param name="lpszWindow">子窗体的名字或控件的Title、Text，通常为显示的文字</param>
        /// <returns></returns>
        [DllImport("user32.dll", EntryPoint = "FindWindowEx", SetLastError = true)]
        private static extern IntPtr FindWindowEx(IntPtr hwndParent, IntPtr hwndChildAfter, string lpszClass, string lpszWindow);


   
        const int WM_SETTEXT = 0x000C; [DllImport("User32.dll", EntryPoint = "SendMessage")]
        private static extern int SendMessage(IntPtr hWnd, uint Msg, int wParam, int lParam);

        /// <summary>/// 发送鼠标点击事件，包含MouseDown和MouseUp/// 
        /// </summary>/// <param name="hwnd">控件句柄</param>
        /// /// <param name="x">鼠标位置x</param>
        /// /// <param name="y">鼠标位置y</param>
        public static void SendMouseClick(IntPtr hwnd, int X, int Y)
        {
            int lparm = (Y << 16) + X;
            int lngResult = SendMessage(hwnd, WM_LBUTTONDOWN, 0, lparm);
            int lngResult2 = SendMessage(hwnd, WM_LBUTTONUP, 0, lparm);
        }
        /// <summary>/// 鼠标按下/// </summary>
        const uint WM_LBUTTONDOWN = 0x0201;
        /// <summary>/// 鼠标抬起/// </summary> 
        const uint WM_LBUTTONUP = 0x0202;

        [StructLayout(LayoutKind.Sequential)]
        public struct RECT
        {
            public int Left;        // x position of upper-left corner
            public int Top;         // y position of upper-left corner
            public int Right;       // x position of lower-right corner
            public int Bottom;      // y position of lower-right corner

            public int Width()
            {
                return Right - Left;
            }

            public int Height()
            {
                return Bottom - Top;
            }
        }

        private string m_classname; // class name to look for
        private string m_caption; // caption name to look for

        public void findTest()
        {
            var wndHandle= FindWindow(null, "天使地图GPS - By:ˇ灬奈絲菟咪球丶");
            if (wndHandle == IntPtr.Zero)
                return;
            IntPtr handle = IntPtr.Zero;
            while (true)
            {
                string XclassName = "Afx:400000:b:10003:900015:0";
                handle = FindWindowEx(wndHandle, handle, XclassName, null);
                if (handle == IntPtr.Zero)
                    return;

                StringBuilder title = new StringBuilder();
                StringBuilder type = new StringBuilder();
                title.Length = 100;
                type.Length = 100;

                GetWindowText(handle, title, 100);//取标题
                GetClassName(handle, type, 100);//取类型
                System.Console.WriteLine($"{handle:x} {title} {type}");
            }
        }
        public string GetGPSValue(IntPtr fatherHandle)
        {
            IntPtr handle = IntPtr.Zero;

            StringBuilder title = new StringBuilder();
            StringBuilder type = new StringBuilder();
            title.Length = 100;
            type.Length = 100;
            while (true)
            {
                string XclassName = "Afx:400000:b:10003:900015:0";
                handle = FindWindowEx(fatherHandle, handle, XclassName, null);
                if (handle == IntPtr.Zero)
                    return "";


                GetWindowText(handle, title, 100);//取标题
                GetClassName(handle, type, 100);//取类型
                if (title.ToString().StartsWith("当前坐标"))
                    return title.ToString().Substring(5); ;
            }
        }

        
        public MyFindWindow()
        { }
      

        private findCallBack m_findObjectCB =null;
        public MyFindWindow(findCallBack _cb)
        {
            m_findObjectCB = _cb;
            m_caption = ObjectInfo.filterName;
            //  m_objInfo = objList;
            EnumWindowProc ecw = new EnumWindowProc(EnumChild);
            EnumChildWindows(IntPtr.Zero, ecw, IntPtr.Zero);

        }
        public void SendMyKey(IntPtr parentHwnd, EnumWindowProc _proc)
        {
            EnumChildWindows(parentHwnd, _proc, IntPtr.Zero);
        }
        private int loopCnt = 0;
        private bool EnumChild(IntPtr handle, IntPtr lParam)
        {
            loopCnt++;
            StringBuilder title = new StringBuilder();
            StringBuilder type = new StringBuilder();
            title.Length = 100;
            type.Length = 100;

            GetWindowText(handle, title, 100);//取标题
            GetClassName(handle, type, 100);//取类型


            if (m_findObjectCB != null )
            {             
                RECT rt = new RECT();
                bool locationLookupSucceeded = GetWindowRect(handle,ref rt);
                int processid = 0;
                GetWindowThreadProcessId(handle,out processid);
                m_findObjectCB(handle,type.ToString(), title.ToString(), rt,processid);                
            }
            return true;
        }

       public  delegate void findCallBack(IntPtr handle,string classType,string title,RECT rt,int processid);

    }
     class FindObjectInfo
    {
        public delegate void FindObjectCB(ObjectInfo _objectInfo);
        public FindObjectInfo(FindObjectCB _cb)
        {
            m_findObjectCB = _cb;
            MyFindWindow fw = new MyFindWindow(findCallBack);
        }

        void findCallBack(IntPtr handle, string classType, string title, RECT rt, int processid)
        {
            if (m_findObjectCB != null && classType.ToString() == "SlOnline")
                m_findObjectCB(new ObjectInfo(handle, title, rt, processid));
        }
        FindObjectCB m_findObjectCB = null;

    }
    class FindSL_GPSHeler
    {
        public delegate void FindCallBackX(IntPtr handle, string classType, string title, RECT rt, int processid);
        private FindCallBackX m_findObjectCB = null;

        void findCallBack(IntPtr handle, string classType, string title, RECT rt, int processid)
        {
            if (m_findObjectCB != null &&classType== "WTWindow" && title.ToString()== "天使地图GPS - By:ˇ灬奈絲菟咪球丶")
                m_findObjectCB(handle, classType, title, rt, processid);
        }
        MyFindWindow fw = null;
        public FindSL_GPSHeler(FindCallBackX _cb)
        {
            m_findObjectCB = _cb;
            fw = new MyFindWindow(findCallBack);
            
        }
        public string GetGPSValue(IntPtr fatherHandle)
        {
            return fw.GetGPSValue(fatherHandle);
        }
    }
}