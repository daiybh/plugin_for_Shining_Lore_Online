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
namespace Guagua
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            this.Text = "guagua  1.0.0.9";
            this.notifyIcon1.Text = this.Text;
            trackBar_H.Value = GolbalSetting.GetInstance().step_H;
            trackBar1_W.Value = GolbalSetting.GetInstance().step_W;            
        }

        ///updatecomplete:8888 /gwip:39.103.187.181  /win /qwllioerjkca8912z9x /login:ainits※52651373
        private IList<ObjectInfo> m_objInfo=new List<ObjectInfo>();

        private List<ObjectInfoWorker> m_objInfoWorker = new List<ObjectInfoWorker>();
        void findCB(ObjectInfo objectInfo)
        {
           var b =  m_objInfo.FirstOrDefault(v => v.userName == objectInfo.userName);
            if (b != null)
            {
                return; 
            }
            var a = m_objInfo.FirstOrDefault(v => v.processID == objectInfo.processID);
            if (a != null)
            {
                a.userName = objectInfo.userName; ;
                return;
            }
            objectInfo.setGraphics( this.CreateGraphics());
            GolbalSetting.GetInstance().updateConfig(ref objectInfo);
            m_objInfo.Add(objectInfo);
            Console.WriteLine(objectInfo.ToString());
            
            //listView1.Items.Add(objectInfo.userName);

            m_objInfoWorker.Add(new ObjectInfoWorker(objectInfo,autoEvent));
        }
      
        private bool bInited = false;
        private void Form1_Load(object sender, EventArgs e)
        {
            splitContainer1.Panel1Collapsed = true;
            MyFindWindow fw = new MyFindWindow(findCB);
            
            bInited = true;
            //  listView1.datas = new ControlBindingsCollection();
            dataGridView1.DataSource = m_objInfo;
            for(int i=0;i<20;i++)
            {
                threadSleep.Items.Add(i);
            }
            // threadSleep.SelectedIndex = 5;
            threadSleep.Text = GolbalSetting.GetInstance().threadSleep.ToString();

            ///  dataGridView1.AutoGenerateColumns = true;
        }

        private void button5_Click(object sender, EventArgs e)
        {
            splitContainer1.Panel1Collapsed = !splitContainer1.Panel1Collapsed;
            button5.Text = (splitContainer1.Panel1Collapsed) ? "^设置^" : "V设置V";
        }
        private void button1_Click(object sender, EventArgs e)
        {
            //splitContainer1.Panel1.Visible = !splitContainer1.Panel1.Visible;
            if (button1.Text == "开始")
            {
                foreach (var worker in m_objInfoWorker)
                {
                    worker.startWork();
                }
                // m_objInfo[listBox1.SelectedIndex].startWork();
                button1.Text = "停止";
            }
            else
            {

                foreach (var worker in m_objInfoWorker)
                {
                    worker.stopWork();
                }
                //m_objInfo[listBox1.SelectedIndex].stopWork();
                button1.Text = "开始";
            }
            // createTextBitmap(m_objInfo[listBox1.SelectedIndex].userName);

        }

        ManualResetEvent autoEvent = new ManualResetEvent(true);
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
            foreach (var oi in m_objInfo)
            {
                oi.showWindow(true);
                
            }
            GolbalSetting.GetInstance().savetoConfig(m_objInfo);
        }

        private void button2_Click(object sender, EventArgs e)
        {
            MyFindWindow fw = new MyFindWindow(findCB);
        }

        private void 显示ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            showThisWindow();
        }

        void showThisWindow()
        {
            this.Visible = true;
            this.WindowState = FormWindowState.Normal;
            this.Show();
        }
        private void 退出ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Form1_FormClosed(sender,null);
        }

        private void Form1_Resize(object sender, EventArgs e)
        {
            if (this.WindowState == FormWindowState.Minimized)
            {
                this.Visible = false;
                this.notifyIcon1.Visible = true;
            }
        }

        private void notifyIcon1_MouseDoubleClick(object sender, MouseEventArgs e)
        {
            showThisWindow();
        }

        private void 隐藏窗口_Click(object sender, EventArgs e)
        {
            bool bShow = false;
            if (button4.Text == "隐藏窗口")
            {
                button4.Text = "显示窗口";
            }
            else
            {
                button4.Text = "隐藏窗口";
                bShow = true;
            }

            foreach (var oi in m_objInfo)
            {
                oi.showWindow(bShow);
            }
        }

        private void dataGridView1_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {
            dataGridView1.CommitEdit(DataGridViewDataErrorContexts.Commit);
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            this.dataGridView1.Refresh();
        }

        private void threadSleep_TextUpdate(object sender, EventArgs e)
        {         
            try
            {
                GolbalSetting.GetInstance().threadSleep = Int32.Parse(threadSleep.Text);
            }
            catch (Exception ex)
            {

            }
        }
    }
}
