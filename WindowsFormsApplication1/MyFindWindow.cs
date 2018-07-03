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


        
        public MyFindWindow()
        { }
      

        private findObjectCB m_findObjectCB=null;
        public MyFindWindow(findObjectCB _cb)
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
            //StringBuilder type = new StringBuilder();
            title.Length = 100;
            //type.Length = 100;

            GetWindowText(handle, title, 100);//取标题
                                              //GetClassName(handle, type, 100);//取类型


            if (m_findObjectCB != null && title.ToString().Contains(m_caption))
            {
             
                RECT rt = new RECT();
                bool locationLookupSucceeded = GetWindowRect(handle,ref rt);
                int processid = 0;
                GetWindowThreadProcessId(handle,out processid);
                m_findObjectCB(new ObjectInfo(handle, title.ToString(), rt,processid));
                //m_objInfo.Add(new ObjectInfo(handle, title.ToString(), rt));
            }
            return true;
        }


    }
}