using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Configuration;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;
using static Guagua.MyFindWindow;
using System.Text.Json;
using System.Text.Json.Serialization;
namespace Guagua
{
    public partial class Form2 : Form
    {
        public Form2()
        {
            InitializeComponent();

            this.Text = "guagua  2.0.0.10";

            loadConfig();

        }
        public class WeatherForecast
        {
            public DateTimeOffset Date { get; set; }
            public int TemperatureCelsius { get; set; }
            public string Summary { get; set; }
        }
        void loadConfig()
        {
            try
            {
                var weatherForecast = new WeatherForecast
                {
                    Date = DateTime.Parse("2019-08-01"),
                    TemperatureCelsius = 25,
                    Summary = "Hot"
                };

                string jsonString = JsonSerializer.Serialize(weatherForecast);

                Console.WriteLine(jsonString);
            }
            catch (Exception ex)
            {

            }
        }
        void saveConfig()
        {
            Configuration appConfig = ConfigurationManager.OpenExeConfiguration(ConfigurationUserLevel.None);   //打开 vshost.exe.config
            appConfig.AppSettings.Settings.Add("mainGameprocessId", curSelectedObjectInfo.processID.ToString());
            appConfig.AppSettings.Settings.Add("GPSProcessId", gPSObject.hWnd.ToString());
            appConfig.AppSettings.Settings.Add("centerXY", buttonGPSValue.Text);
            appConfig.Save();
        }

        ManualResetEvent autoEvent = new ManualResetEvent(true);
        private IList<ObjectInfo> m_objInfo = new List<ObjectInfo>();


        ObjectInfoWorker objectInfoWorker = null;
        void findCB(ObjectInfo objectInfo)
        {
            var b = m_objInfo.FirstOrDefault(v => v.userName == objectInfo.userName);
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
            objectInfo.setGraphics(this.CreateGraphics());
            GolbalSetting.GetInstance().updateConfig(ref objectInfo);
            m_objInfo.Add(objectInfo);
            Console.WriteLine(objectInfo.ToString());

            //listView1.Items.Add(objectInfo.userName);



            NamecomboBox.Items.Add(objectInfo);
            NamecomboBox.SelectedIndex = 0;
        }
        class GPSObject
        {
            public GPSObject(IntPtr handle, string classType, string title, RECT rt, int processid)
            {
                this.hWnd = handle;
                this.classType = classType;
                this.title = title;
                this.rt = rt;
                this.processid = processid;
            }
            public override string ToString()
            {
                return string.Format("pid:{0} title:{1}", this.processid, this.title);
            }

            public IntPtr hWnd;
            string classType; string title;
            RECT rt;
            int processid;

        }
        void FindSL_GPSHeler_CB(IntPtr handle, string classType, string title, RECT rt, int processid)
        {

            comboBoxGPS.Items.Add(new GPSObject(handle, classType, title, rt, processid));
        }
        FindSL_GPSHeler findSL_GPSHeler = null;
        private void Form2_Load(object sender, EventArgs e)
        {
            objectInfoWorker = new ObjectInfoWorker(autoEvent);
            FindObjectInfo findObjectInfo = new FindObjectInfo(findCB);
            findSL_GPSHeler = new FindSL_GPSHeler(FindSL_GPSHeler_CB);
        }
        bool bNeedGoCenter = false;
        (int, int) getCurrentGPSPos()
        {
            string currentGPSText = label14.Text;
            var gps = currentGPSText.Split(',');
            if (gps.Length != 2) return (0,0);
            int centerX = int.Parse(gps[0]);
            int centerY = int.Parse(gps[1]);
            return (centerX, centerY);
        }
        void goto_Center(int x1,int y1,int x4,int y4)
        {            
            label13.Text = label14.Text; 
            var (centerX, centerY )= getCurrentGPSPos();
            if (centerX == 0 && centerY == 0) return;
            if (centerX < x1)
            {
                if (centerY < y1)
                {
                    label13.Text = "小于 x1 y1 往左下走";
                    curSelectedObjectInfo.move_left_down_one(); bNeedGoCenter = true;
                }
                else if (centerY > y4)
                {
                    label13.Text = "超出 x1 y4  往左上走";
                    curSelectedObjectInfo.move_left_top_one(); bNeedGoCenter = true;
                }
                else
                {
                    label13.Text = "x1 超出 y 没有超出 往左";
                    curSelectedObjectInfo.move_left_one(); bNeedGoCenter = true;
                }
            }
            else if (centerX > x1 && centerX < x4)
            {
                if (centerY < y1)
                {
                    label13.Text = "x1 没超出 y1 小了 往下走";
                    curSelectedObjectInfo.move_down_one(); bNeedGoCenter = true;
                }
                else if (centerY > y4)
                {
                    label13.Text = "x1 没超出 y1 大了 往上走";
                    curSelectedObjectInfo.move_top_one(); bNeedGoCenter = true;
                }
            }
            else if (centerX > x4)
            {
                if (centerY < y1)
                {
                    label13.Text = "小于 x1 y1 往右下走";
                    curSelectedObjectInfo.move_right_down_one(); bNeedGoCenter = true;
                }
                else if (centerY > y4)
                {
                    label13.Text = "超出 x1 y4  往右上走";
                    curSelectedObjectInfo.move_right_top_one(); bNeedGoCenter = true;
                }
                else
                {
                    label13.Text = "x1 超出 y 没有超出 往右走";
                    curSelectedObjectInfo.move_right_one(); bNeedGoCenter = true;
                }
            }

            else if (centerY < y1)
            {
                if (centerX < x1)
                {
                    label13.Text = "小于x1  往左下走";
                    curSelectedObjectInfo.move_left_down_one(); bNeedGoCenter = true;
                }
                else if (centerX > x4)
                {
                    label13.Text = "大于x4  往右下走";
                    curSelectedObjectInfo.move_right_down_one(); bNeedGoCenter = true;
                }
                else
                {
                    label13.Text = "y1 超出 x 没有超出 往下";
                    curSelectedObjectInfo.move_down_one(); bNeedGoCenter = true;
                }
            }
            else if (centerY > y4)
            {
                if (centerX < x1)
                {
                    label13.Text = "小于x1  往左上走";
                    curSelectedObjectInfo.move_left_top_one(); bNeedGoCenter = true;
                }
                else if (centerX > x4)
                {
                    label13.Text = "大于x4  往右上走";
                    curSelectedObjectInfo.move_right_top_one(); bNeedGoCenter = true;
                }
                else
                {
                    label13.Text = "y1 超出 x 没有超出 往上";
                    curSelectedObjectInfo.move_top_one(); bNeedGoCenter = true;
                }
            }
            else if (centerY > y1 && centerY < y4)
            {
                if (centerX < x1)
                {
                    label13.Text = "小于x1  往左走";
                    curSelectedObjectInfo.move_left_one(); bNeedGoCenter = true;
                }
                else if (centerX > x4)
                {
                    label13.Text = "大于x1  往右走";
                    curSelectedObjectInfo.move_right_one(); bNeedGoCenter = true;
                }
            }

            //curSelectedObjectInfo.attackCenter();
            System.Console.WriteLine(label13.Text);
        }
        void checkIfoutGPS()
        {
        
            // while (true)
            {
                try
                {
                    if (bNeedGoCenter)
                    {
                        int offset = 0;
                        goto_Center(gpsCenterX- offset, gpsCenterY- offset, gpsCenterX+ offset, gpsCenterY+ offset);

                        //check if is in center
                        var (x,y)= getCurrentGPSPos();
                        if (x == gpsCenterX && y == gpsCenterY)
                        {
                            bNeedGoCenter = false;
                        }

                        
                    }
                    else
                    {
                        goto_Center(int.Parse(x1.Text), int.Parse(y1.Text), int.Parse(x4.Text), int.Parse(y4.Text));
                    }
                }
                catch (Exception ex)
                {

                }
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {

            if (button1.Text == "开始")
            {
                button1.Text = "停止";
                objectInfoWorker.startWork();
            }
            else
            {
                button1.Text = "开始";
                objectInfoWorker.stopWork();
            }
        }
        ObjectInfo curSelectedObjectInfo = null;
        private void timer1_Tick(object sender, EventArgs e)
        {
            if (curSelectedObjectInfo != null)
                NPValue.Text = curSelectedObjectInfo.currentNP;

            if (gPSObject != null)
                label14.Text = findSL_GPSHeler.GetGPSValue(gPSObject.hWnd);

            checkIfoutGPS();
        }

        private void NamecomboBox_SelectedValueChanged(object sender, EventArgs e)
        {
            if (curSelectedObjectInfo != null)
                curSelectedObjectInfo.enableWork = false;

            ObjectInfo objectInfo = NamecomboBox.SelectedItem as ObjectInfo;
            curSelectedObjectInfo = objectInfo;
            curSelectedObjectInfo.enableWork = true;

            objectInfoWorker.setObject(objectInfo);

        }

        private void button2_MouseDown(object sender, MouseEventArgs e)
        {

        }
        GPSObject gPSObject = null;
        private void comboBoxGPS_SelectedValueChanged(object sender, EventArgs e)
        {
            gPSObject = comboBoxGPS.SelectedItem as GPSObject;
        }
        int gpsCenterX = 0;
        int gpsCenterY = 0;
        private void buttonGPSValue_Click(object sender, EventArgs e)
        {
            //buttonGPSValue.Text = label14.Text;


            string centerGPS = label14.Text;
            var gps = centerGPS.Split(',');
            int centerX = int.Parse(gps[0]);
            int centerY = int.Parse(gps[1]);
            
            gpsCenterX = centerX;
            gpsCenterY = centerY;

            int OffsetX = 3;
            x1.Text = (centerX - OffsetX).ToString();
            y1.Text = (centerY - OffsetX).ToString();
            x2.Text = (centerX + OffsetX).ToString();
            y2.Text = (centerY - OffsetX).ToString();

            x3.Text = (centerX - OffsetX).ToString();
            y3.Text = (centerY + OffsetX).ToString();
            x4.Text = (centerX + OffsetX).ToString();
            y4.Text = (centerY + OffsetX).ToString();
            saveConfig();
        }



        private void button_TOP_Click(object sender, EventArgs e)
        {
            curSelectedObjectInfo.move_top_one();
        }

        private void button_down_Click(object sender, EventArgs e)
        {

            curSelectedObjectInfo.move_down_one();
        }

        private void button_left_Click(object sender, EventArgs e)
        {

            curSelectedObjectInfo.move_left_one();
        }

        private void button_right_Click(object sender, EventArgs e)
        {

            curSelectedObjectInfo.move_right_one();
        }

        private void button_top_left_Click(object sender, EventArgs e)
        {

            curSelectedObjectInfo.move_left_top_one();
        }

        private void top_right_Click(object sender, EventArgs e)
        {
            curSelectedObjectInfo.move_right_top_one();
        }

        private void down_left_Click(object sender, EventArgs e)
        {
            curSelectedObjectInfo.move_left_down_one();
        }

        private void down_Right_Click(object sender, EventArgs e)
        {
            curSelectedObjectInfo.move_right_down_one();
        }
    }
}
