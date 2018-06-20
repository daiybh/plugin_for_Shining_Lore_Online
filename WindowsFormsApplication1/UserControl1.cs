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
        Dictionary<string ,int> comboSource = new Dictionary<string, int>();
        public UserControl1()
        {
            InitializeComponent();
            for (int i = 0; i < 9; i++)
            {
                int curvalue = (i + 1) * 10;
                comboSource.Add(curvalue.ToString()+"%",curvalue);
            }
            comboBox1.DataSource = new BindingSource(comboSource,null);
            comboBox1.DisplayMember = "Key";
            comboBox1.ValueMember = "Value";
        }
        public String Title { get; set; }
        private void UserControl1_Load(object sender, EventArgs e)
        {
            checkBox_Enable.Text = Title;
            if (Title == "HP")
            {
                checkBox_Enable.Checked = GolbalSetting.GetInstance().keyPress_HP[0];
                checkBox1.Checked = GolbalSetting.GetInstance().keyPress_HP[1];
                checkBox2.Checked = GolbalSetting.GetInstance().keyPress_HP[2];
                checkBox3.Checked = GolbalSetting.GetInstance().keyPress_HP[3];
                checkBox4.Checked = GolbalSetting.GetInstance().keyPress_HP[4];
                checkBox5.Checked = GolbalSetting.GetInstance().keyPress_HP[5];
                comboBox1.SelectedIndex =  GolbalSetting.GetInstance().HPPercent ;
            }
            else if (Title == "SP")
            {
                checkBox_Enable.Checked = GolbalSetting.GetInstance().keyPress_SP[0];

                checkBox1.Checked = GolbalSetting.GetInstance().keyPress_SP[1];
                checkBox2.Checked = GolbalSetting.GetInstance().keyPress_SP[2];
                checkBox3.Checked = GolbalSetting.GetInstance().keyPress_SP[3];
                checkBox4.Checked = GolbalSetting.GetInstance().keyPress_SP[4];
                checkBox5.Checked = GolbalSetting.GetInstance().keyPress_SP[5];
                comboBox1.SelectedIndex = GolbalSetting.GetInstance().SPPercent;
            }
            else if (Title == "NP")
            {
                checkBox_Enable.Checked = GolbalSetting.GetInstance().keyPress_NP[0];
                checkBox1.Checked = GolbalSetting.GetInstance().keyPress_NP[1];
                checkBox2.Checked = GolbalSetting.GetInstance().keyPress_NP[2];
                checkBox3.Checked = GolbalSetting.GetInstance().keyPress_NP[3];
                checkBox4.Checked = GolbalSetting.GetInstance().keyPress_NP[4];
                checkBox5.Checked = GolbalSetting.GetInstance().keyPress_NP[5];
                comboBox1.SelectedIndex = GolbalSetting.GetInstance().NPPercent;
            }



            checkBox1.CheckedChanged += CheckBox1_CheckedChanged;
            checkBox2.CheckedChanged += CheckBox1_CheckedChanged;
            checkBox3.CheckedChanged += CheckBox1_CheckedChanged;
            checkBox4.CheckedChanged += CheckBox1_CheckedChanged;
            checkBox5.CheckedChanged += CheckBox1_CheckedChanged;
            comboBox1.SelectedIndexChanged += CheckBox1_CheckedChanged; ;
            checkBox_Enable.CheckedChanged += CheckBox1_CheckedChanged;
        }
        

        private void CheckBox1_CheckedChanged(object sender, EventArgs e)
        {
            if (Title == "NP")
            {
                GolbalSetting.GetInstance().keyPress_NP[0] = this.checkBox_Enable.Checked;
                GolbalSetting.GetInstance().keyPress_NP[1] = this.checkBox1.Checked;
                GolbalSetting.GetInstance().keyPress_NP[2] = this.checkBox2.Checked;
                GolbalSetting.GetInstance().keyPress_NP[3] = this.checkBox3.Checked;
                GolbalSetting.GetInstance().keyPress_NP[4] = this.checkBox4.Checked;
                GolbalSetting.GetInstance().keyPress_NP[5] = this.checkBox5.Checked;
                GolbalSetting.GetInstance().NPPercent = comboBox1.SelectedIndex;
            }
            else if (Title == "HP")
            {
                GolbalSetting.GetInstance().keyPress_HP[0] = this.checkBox_Enable.Checked;
                GolbalSetting.GetInstance().keyPress_HP[1] = this.checkBox1.Checked;
                GolbalSetting.GetInstance().keyPress_HP[2] = this.checkBox2.Checked;
                GolbalSetting.GetInstance().keyPress_HP[3] = this.checkBox3.Checked;
                GolbalSetting.GetInstance().keyPress_HP[4] = this.checkBox4.Checked;
                GolbalSetting.GetInstance().keyPress_HP[5] = this.checkBox5.Checked;
                GolbalSetting.GetInstance().HPPercent = comboBox1.SelectedIndex;
            }
            else if (Title == "SP")
            {
                GolbalSetting.GetInstance().keyPress_SP[0] = this.checkBox_Enable.Checked;
                GolbalSetting.GetInstance().keyPress_SP[1] = this.checkBox1.Checked;
                GolbalSetting.GetInstance().keyPress_SP[2] = this.checkBox2.Checked;
                GolbalSetting.GetInstance().keyPress_SP[3] = this.checkBox3.Checked;
                GolbalSetting.GetInstance().keyPress_SP[4] = this.checkBox4.Checked;
                GolbalSetting.GetInstance().keyPress_SP[5] = this.checkBox5.Checked;
                GolbalSetting.GetInstance().SPPercent = comboBox1.SelectedIndex;
            }
        }
    }
}
