using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using QM_GUI_Bkgnd;

namespace WindowsFormsApplication2
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }
        class MyStruct
        {
            public string Name { get; set; }
            public string Adres { get; set; }
            public bool IsShow { get; set; }


            public MyStruct(string name, string adress)
            {
                Name = name;
                Adres = adress;
                IsShow = false;
            }
        }
        private void Form1_KeyPress(object sender, KeyPressEventArgs e)
        {
            int x = e.KeyChar;
            this.listBox1.Items.Add(string.Format("keyPress-->{0},{1},{2}",e.KeyChar, x, list.Count));
            list.Add(new MyStruct(e.KeyChar.ToString(),string.Format("{0}",list.Count)));
            dataGridView1.Refresh();
            
        }

        private List<MyStruct> list=null;
        private void Form1_Load(object sender, EventArgs e)
        {
            var source = new BindingSource();
            list= new List<MyStruct> { new MyStruct("fff", "b"), new MyStruct("c", "d") };
            source.DataSource = list;
            dataGridView1.DataSource = source;
        }
    }
}
