using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Configuration;
namespace WindowsFormsApplication1
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            this.Text = "guagua  1.0.0.5";
            trackBar_H.Value = GolbalSetting.GetInstance().step_H;
            trackBar1_W.Value = GolbalSetting.GetInstance().step_W;
            
        }
        private Thread t1 = null;
        private bool bExit = false;

        ManualResetEvent autoEvent = new ManualResetEvent(true);
        public void doWorkThread()
        {
            int X = 0;
            int Y = 0;

            //发送键盘按键 +
            for (int i = 0; i < 10; i++)
            {
                foreach (var oi in m_objInfo)
                {
                    MouseEvent.moveMouse(oi.hWnd, oi.center_X + i * 10, oi.center_y + i * 10);
                    MouseEvent.pressKey(oi.hWnd, Keys.Add);
                }
                Thread.Sleep(1000);
            }
            Thread.Sleep(100);
            while (!bExit)
            {
                foreach (var oi in m_objInfo)
                {
                    if(oi.enableWork)
                        MouseEvent.pressKey(oi.hWnd, Keys.Z);
                }
                //RightAttack(center_X, center_y);
                for (int h =ObjectInfo.Object_H * -1; h < 10; h += GolbalSetting.GetInstance().step_H)
                {
                    for (int w = -45; w < 30; w += GolbalSetting.GetInstance().step_W)
                    {
                        foreach (var oi in m_objInfo)
                        {
                            if(!oi.enableWork)continue;
                            X = oi.center_X + w;
                            Y = oi.center_y + h;

                            oi.attack(X, Y);
                            oi.screenshotting();

                        }
                        autoEvent.WaitOne();
                    }
                }

            }
        }

        
        public void startWork()
        {
            t1 = new Thread(new ThreadStart(doWorkThread));
            t1.IsBackground = true;
            t1.Start();
        }

        public void stopWork()
        {
            bExit = true;
            if (t1 != null && t1.IsAlive)
                t1.Abort();
        }

        private List<ObjectInfo> m_objInfo=new List<ObjectInfo>();

        void findCB(ObjectInfo objectInfo)
        {
            objectInfo.g = this.CreateGraphics();
            objectInfo.enableWork = true;
            m_objInfo.Add(objectInfo);
            Console.WriteLine(objectInfo.ToString());
            listBox1.Items.Add(objectInfo.userName);
            listView1.Items.Add(objectInfo.userName);

        }
        

        private bool bInited = false;
        private void Form1_Load(object sender, EventArgs e)
        {
            MyFindWindow fw = new MyFindWindow(findCB);
            listBox1.SelectedIndex = 0;
            bInited = true;
        }
        private void button1_Click(object sender, EventArgs e)
        {
            if (button1.Text == "开始")
            {
               startWork();
                // m_objInfo[listBox1.SelectedIndex].startWork();
                button1.Text = "停止";
            }
            else
            {
                stopWork();
                //m_objInfo[listBox1.SelectedIndex].stopWork();
                button1.Text = "开始";
            }
            // createTextBitmap(m_objInfo[listBox1.SelectedIndex].userName);

        }
        private void button3_Click(object sender, EventArgs e)
        {
            if (button3.Text == "暂停")
            {
                autoEvent.Reset();
            }
            else
            {
                autoEvent.Set();
            }
            button3.Text = (button3.Text == "暂停") ? "继续运行" : "暂停";
        }
        private void listView1_ItemChecked(object sender, ItemCheckedEventArgs e)
        {
            if (!bInited) return;
           m_objInfo[e.Item.Index].enableWork=(e.Item.Checked);
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

        private void trackBar_H_ValueChanged(object sender, EventArgs e)
        {
            if (!bInited) return;
            GolbalSetting.GetInstance().step_H = trackBar_H.Value;
            
        }

        private void trackBar1_W_ValueChanged(object sender, EventArgs e)
        {
            if (!bInited) return;
            GolbalSetting.GetInstance().step_W = trackBar1_W.Value;
           
        }

        private void Form1_FormClosed(object sender, FormClosedEventArgs e)
        {
            GolbalSetting.GetInstance().savetoConfig();
        }
    }
}
