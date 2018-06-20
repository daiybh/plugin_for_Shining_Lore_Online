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
            GolbalSetting.GetInstance().LoadConfig();
            trackBar_H.Value = GolbalSetting.GetInstance().step_H;
            trackBar1_W.Value = GolbalSetting.GetInstance().step_W;
            userControl_HP.isEnable = GolbalSetting.GetInstance().keyPress_HP[0];
            userControl_SP.isEnable = GolbalSetting.GetInstance().keyPress_SP[0];
            userControl_NP.isEnable = GolbalSetting.GetInstance().keyPress_NP[0];

            {
                userControl_HP.pressKey1 = GolbalSetting.GetInstance().keyPress_HP[1];
                userControl_HP.pressKey2 = GolbalSetting.GetInstance().keyPress_HP[2];
                userControl_HP.pressKey3 = GolbalSetting.GetInstance().keyPress_HP[3];
                userControl_HP.pressKey4 = GolbalSetting.GetInstance().keyPress_HP[4];
                userControl_HP.pressKey5 = GolbalSetting.GetInstance().keyPress_HP[5];
           }
            {
                userControl_SP.pressKey1 = GolbalSetting.GetInstance().keyPress_SP[1];
                userControl_SP.pressKey2 = GolbalSetting.GetInstance().keyPress_SP[2];
                userControl_SP.pressKey3 = GolbalSetting.GetInstance().keyPress_SP[3];
                userControl_SP.pressKey4 = GolbalSetting.GetInstance().keyPress_SP[4];
                userControl_SP.pressKey5 = GolbalSetting.GetInstance().keyPress_SP[5];
            }
            {
                userControl_NP.pressKey1 = GolbalSetting.GetInstance().keyPress_NP[1];
                userControl_NP.pressKey2 = GolbalSetting.GetInstance().keyPress_NP[2];
                userControl_NP.pressKey3 = GolbalSetting.GetInstance().keyPress_NP[3];
                userControl_NP.pressKey4 = GolbalSetting.GetInstance().keyPress_NP[4];
                userControl_NP.pressKey5 = GolbalSetting.GetInstance().keyPress_NP[5];
            }
        }

        private List<ObjectInfo> m_objInfo=new List<ObjectInfo>();

        void findCB(ObjectInfo objectInfo)
        {
            objectInfo.g = this.CreateGraphics();
            m_objInfo.Add(objectInfo);
            Console.WriteLine(objectInfo.ToString());
            listBox1.Items.Add(objectInfo.userName);
            listView1.Items.Add(objectInfo.userName);
        }
        void findAngle()
        {
            MyFindWindow fw = new MyFindWindow(findCB);
        }

        private bool bInited = false;
        private void Form1_Load(object sender, EventArgs e)
        {
           findAngle();
            listBox1.SelectedIndex = 0;
            bInited = true;
        }
        private void button1_Click(object sender, EventArgs e)
        {
            // m_objInfo[listBox1.SelectedIndex].attack(540,768/2);
            if (button1.Text == "开始")
            {
                m_objInfo[listBox1.SelectedIndex].startWork();
                button1.Text = "停止";
            }
            else
            {
                m_objInfo[listBox1.SelectedIndex].stopWork();
                button1.Text = "开始";
            }
            // createTextBitmap(m_objInfo[listBox1.SelectedIndex].userName);

        }
        private void button3_Click(object sender, EventArgs e)
        {
            m_objInfo[listBox1.SelectedIndex].screenshotting();
            return;
            m_objInfo[listBox1.SelectedIndex].pauseWork();
            button1.Text = (button1.Text == "暂停") ? "继续运行" : "暂停";
        }
       
        private void listView1_ItemChecked(object sender, ItemCheckedEventArgs e)
        {
            if (!bInited) return;
           m_objInfo[e.Item.Index].showWindow(e.Item.Checked);
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
             GolbalSetting.GetInstance().step_H= trackBar_H.Value;
            GolbalSetting.GetInstance().step_W= trackBar1_W.Value ;
             GolbalSetting.GetInstance().keyPress_HP[0]= userControl_HP.isEnable ;
            GolbalSetting.GetInstance().keyPress_SP[0] = userControl_SP.isEnable ;
            GolbalSetting.GetInstance().keyPress_NP[0] = userControl_NP.isEnable ;

            {
                 GolbalSetting.GetInstance().keyPress_HP[1]= userControl_HP.pressKey1 ;
                GolbalSetting.GetInstance().keyPress_HP[2] = userControl_HP.pressKey2 ;
                GolbalSetting.GetInstance().keyPress_HP[3] = userControl_HP.pressKey3 ;
                GolbalSetting.GetInstance().keyPress_HP[4] = userControl_HP.pressKey4 ;
                GolbalSetting.GetInstance().keyPress_HP[5] = userControl_HP.pressKey5 ;
            }
            {
                 GolbalSetting.GetInstance().keyPress_SP[1]= userControl_SP.pressKey1 ;
                GolbalSetting.GetInstance().keyPress_SP[2] = userControl_SP.pressKey2 ;
                GolbalSetting.GetInstance().keyPress_SP[3] = userControl_SP.pressKey3 ;
                GolbalSetting.GetInstance().keyPress_SP[4] = userControl_SP.pressKey4 ;
                GolbalSetting.GetInstance().keyPress_SP[5] = userControl_SP.pressKey5 ;
            }                                              
            {                                              
                 GolbalSetting.GetInstance().keyPress_NP[1] = userControl_NP.pressKey1;
                GolbalSetting.GetInstance().keyPress_NP[2] = userControl_NP.pressKey2 ;
                GolbalSetting.GetInstance().keyPress_NP[3] = userControl_NP.pressKey3 ;
                GolbalSetting.GetInstance().keyPress_NP[4] = userControl_NP.pressKey4 ;
                GolbalSetting.GetInstance().keyPress_NP[5] = userControl_NP.pressKey5 ;
            }

            GolbalSetting.GetInstance().savetoConfig();
        }
    }
}
