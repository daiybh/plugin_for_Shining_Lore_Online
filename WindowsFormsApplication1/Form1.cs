using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsApplication1
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private List<ObjectInfo> m_objInfo;
        void findAngle()
        {
            MyFindWindow fw = new MyFindWindow(ObjectInfo.filterName, null);
            foreach (var va in fw.m_objInfo)
            {
                Console.WriteLine(va.ToString());
                listBox1.Items.Add(va.userName);
            }

            m_objInfo = fw.m_objInfo;
        }
        private void Form1_Load(object sender, EventArgs e)
        {
           findAngle();
        }
        private void button1_Click(object sender, EventArgs e)
        {
            // m_objInfo[listBox1.SelectedIndex].attack(540,768/2);
            m_objInfo[listBox1.SelectedIndex].startWork();
            // createTextBitmap(m_objInfo[listBox1.SelectedIndex].userName);

        }
        private void button3_Click(object sender, EventArgs e)
        {
            m_objInfo[listBox1.SelectedIndex].pauseWork();
        }
        private void button2_Click(object sender, EventArgs e)
        {
            m_objInfo[listBox1.SelectedIndex].stopWork();
        }
        private const int WM_SETTEXT = 0x000C;

        public const int WM_CHAR = 0x0102;
        [DllImport("user32.dll")]
        private static extern IntPtr FindWindow(string lpClassName, string lpWindowName);

        [DllImport("User32.dll")]
        private static extern IntPtr FindWindowEx(IntPtr hwndParent, IntPtr hwndChildAfter, string lpszClass, string lpszWindows);

        [DllImport("User32.dll")]
        private static extern Int32 SendMessage(IntPtr hWnd, int Msg, int wParam, int lParam);

        [DllImport("User32.dll")]
        private static extern Int32 PostMessage(IntPtr hWnd, int Msg, int wParam, int lParam);


        private bool EnumChild(IntPtr handle, IntPtr lParam)
        {
           
            return true;
        }

        private void xxxx()
        {
            // 返回写字板主窗口句柄  
            IntPtr hWnd = FindWindow(null, " 永恒天使 - 654fdsaf");
            //IntPtr hWnd = FindWindow(null, "无标题 - 记事本");
            if (!hWnd.Equals(IntPtr.Zero))
            {
                MyFindWindow fw = new MyFindWindow();
                fw.SendMyKey(hWnd, (IntPtr handle, IntPtr lParam) =>
                {  // MessageBox.Show(string.Format("{0}>>Enumxxxxxx:{1}", saveCount++, handle));

                    Console.WriteLine("{0}>>Enumxxxxxx:{1}", saveCount++, handle);
                    int x = 'k' - 'a';
                    PostMessage(handle, WM_CHAR, 107 - x, 0);
                    PostMessage(handle, 258, 13, 0);
                    return true;
                });
                //返回写字板编辑窗口句柄  
                /* IntPtr edithWnd = FindWindowEx(hWnd, IntPtr.Zero, "Edit", null);
                 if (!edithWnd.Equals(IntPtr.Zero))
                     // 发送WM_SETTEXT 消息： "Hello World!"  
                 {
                     SendMessage(edithWnd, WM_SETTEXT, IntPtr.Zero, new StringBuilder("Hello World!"));
 
                 }/**/
            }
            else
                MessageBox.Show("not found");
        }
        void createTextBitmap(string text)
        {
            Bitmap destBmp = new Bitmap((text.Length+1)*12,16);
            Graphics g = Graphics.FromImage(destBmp);//在刚才新建的图片上新建一个画板
            g.DrawString(text, new Font("宋体", 12), new SolidBrush(Color.Red), new PointF(0f, 0f));
            g.Dispose();//释放目前的这个画板
            
            Graphics g1 = this.CreateGraphics();//重新新建一个Graphics类
            //如果之前那个画板不释放，而直接g=this.CreateGraphics()这样的话无法释放掉第一次创建的g,因为只是把地址转到新的g了．如同string一样
            g1 = this.CreateGraphics();//在整个全屏窗体上新建画板
            g1.DrawImage(destBmp, new Point(0, 0));//将刚才所画的图片画到这个窗体上
            //这个也可以属于二次缓冲技术，如果直接将矩形画在窗体上，会造成图片抖动并且会有无数个矩形．
            g1.Dispose();
            destBmp.Save(string.Format("c:\\jpeg\\111_{0}.jpg", saveCount++));
            destBmp.Dispose();//要及时释放，不然内存将会被大量消耗
        }

        private int saveCount = 0;

    }
}
