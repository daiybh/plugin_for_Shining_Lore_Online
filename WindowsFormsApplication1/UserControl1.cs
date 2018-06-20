using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsApplication1
{
    public partial class UserControl1 : UserControl
    {
        public UserControl1()
        {
            InitializeComponent();
        }
        public String Title { get; set; }
        private void UserControl1_Load(object sender, EventArgs e)
        {
            checkBox_Enable.Text = Title;
            textBox1.Text = lessValue.ToString();
        }

        public int m_value { get; set; } = 1000;
        public bool pressKey1
        {
            get { return checkBox1.Checked; }
            set { checkBox1.Checked = value; }
        }
        public bool pressKey2
        {
            get { return checkBox2.Checked; }
            set { checkBox2.Checked = value; }
        }
        public bool pressKey3
        {
            get { return checkBox3.Checked; }
            set { checkBox3.Checked = value; }
        }
        public bool pressKey4
        {
            get { return checkBox5.Checked; }
            set { checkBox5.Checked = value; }
        }
        public bool pressKey5
        {
            get { return checkBox4.Checked; }
            set { checkBox4.Checked = value; }
        }

        public bool isEnable
        {
            get { return checkBox_Enable.Checked; }
            set { checkBox_Enable.Checked = value; }
        }
        public int lessValue=1000;
        private void checkBox_Enable_CheckedChanged(object sender, EventArgs e)
        {

        }
    }
}
