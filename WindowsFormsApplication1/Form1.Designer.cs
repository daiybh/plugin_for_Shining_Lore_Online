namespace WindowsFormsApplication1
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.listBox1 = new System.Windows.Forms.ListBox();
            this.button1 = new System.Windows.Forms.Button();
            this.button3 = new System.Windows.Forms.Button();
            this.listView1 = new System.Windows.Forms.ListView();
            this.columnHeader2 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnHeader3 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.trackBar_H = new System.Windows.Forms.TrackBar();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.trackBar1_W = new System.Windows.Forms.TrackBar();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.userControl_NP = new WindowsFormsApplication1.UserControl1();
            this.userControl_SP = new WindowsFormsApplication1.UserControl1();
            this.userControl_HP = new WindowsFormsApplication1.UserControl1();
            this.objectInfoBindingSource = new System.Windows.Forms.BindingSource(this.components);
            this.objectInfoBindingSource1 = new System.Windows.Forms.BindingSource(this.components);
            ((System.ComponentModel.ISupportInitialize)(this.trackBar_H)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBar1_W)).BeginInit();
            this.groupBox1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.objectInfoBindingSource)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.objectInfoBindingSource1)).BeginInit();
            this.SuspendLayout();
            // 
            // listBox1
            // 
            this.listBox1.FormattingEnabled = true;
            this.listBox1.Location = new System.Drawing.Point(13, 25);
            this.listBox1.Name = "listBox1";
            this.listBox1.Size = new System.Drawing.Size(51, 108);
            this.listBox1.TabIndex = 0;
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(83, 64);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(75, 23);
            this.button1.TabIndex = 1;
            this.button1.Text = "开始";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // button3
            // 
            this.button3.Location = new System.Drawing.Point(164, 64);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(75, 23);
            this.button3.TabIndex = 2;
            this.button3.Text = "暂停";
            this.button3.UseVisualStyleBackColor = true;
            this.button3.Click += new System.EventHandler(this.button3_Click);
            // 
            // listView1
            // 
            this.listView1.CheckBoxes = true;
            this.listView1.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.columnHeader2,
            this.columnHeader3});
            this.listView1.Location = new System.Drawing.Point(83, 25);
            this.listView1.Name = "listView1";
            this.listView1.Size = new System.Drawing.Size(253, 33);
            this.listView1.TabIndex = 3;
            this.listView1.UseCompatibleStateImageBehavior = false;
            this.listView1.View = System.Windows.Forms.View.Details;
            this.listView1.ItemChecked += new System.Windows.Forms.ItemCheckedEventHandler(this.listView1_ItemChecked);
            // 
            // columnHeader2
            // 
            this.columnHeader2.Text = "Name";
            this.columnHeader2.Width = 193;
            // 
            // columnHeader3
            // 
            this.columnHeader3.Text = "other";
            // 
            // trackBar_H
            // 
            this.trackBar_H.Location = new System.Drawing.Point(83, 295);
            this.trackBar_H.Maximum = 100;
            this.trackBar_H.Name = "trackBar_H";
            this.trackBar_H.Size = new System.Drawing.Size(230, 45);
            this.trackBar_H.TabIndex = 4;
            this.trackBar_H.Value = 3;
            this.trackBar_H.ValueChanged += new System.EventHandler(this.trackBar_H_ValueChanged);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(0, 0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(35, 13);
            this.label1.TabIndex = 5;
            this.label1.Text = "label1";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(7, 295);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(70, 13);
            this.label2.TabIndex = 6;
            this.label2.Text = "高度步进值:";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(7, 346);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(70, 13);
            this.label3.TabIndex = 8;
            this.label3.Text = "宽度步进值:";
            // 
            // trackBar1_W
            // 
            this.trackBar1_W.Location = new System.Drawing.Point(83, 346);
            this.trackBar1_W.Maximum = 100;
            this.trackBar1_W.Name = "trackBar1_W";
            this.trackBar1_W.Size = new System.Drawing.Size(230, 45);
            this.trackBar1_W.TabIndex = 7;
            this.trackBar1_W.Value = 3;
            this.trackBar1_W.ValueChanged += new System.EventHandler(this.trackBar1_W_ValueChanged);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.userControl_NP);
            this.groupBox1.Controls.Add(this.userControl_SP);
            this.groupBox1.Controls.Add(this.userControl_HP);
            this.groupBox1.Location = new System.Drawing.Point(3, 139);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(316, 137);
            this.groupBox1.TabIndex = 9;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "吃药设置";
            // 
            // userControl_NP
            // 
            
            this.userControl_NP.Location = new System.Drawing.Point(10, 102);
            this.userControl_NP.Name = "userControl_NP";
            this.userControl_NP.Size = new System.Drawing.Size(289, 28);
            this.userControl_NP.TabIndex = 2;
            this.userControl_NP.Title = "NP";
            // 
            // userControl_SP
            // 
            this.userControl_SP.Location = new System.Drawing.Point(10, 61);
            this.userControl_SP.Name = "userControl_SP";
            this.userControl_SP.Size = new System.Drawing.Size(289, 28);
            this.userControl_SP.TabIndex = 1;
            this.userControl_SP.Title = "SP";
            // 
            // userControl_HP
            // 
            
            this.userControl_HP.Location = new System.Drawing.Point(10, 20);
            
            this.userControl_HP.Name = "userControl_HP";
            
            this.userControl_HP.Size = new System.Drawing.Size(289, 28);
            this.userControl_HP.TabIndex = 0;
            this.userControl_HP.Title = "HP";
            // 
            // objectInfoBindingSource
            // 
            this.objectInfoBindingSource.DataSource = typeof(WindowsFormsApplication1.ObjectInfo);
            // 
            // objectInfoBindingSource1
            // 
            this.objectInfoBindingSource1.DataSource = typeof(WindowsFormsApplication1.ObjectInfo);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(329, 409);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.trackBar1_W);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.trackBar_H);
            this.Controls.Add(this.listView1);
            this.Controls.Add(this.button3);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.listBox1);
            this.Name = "Form1";
            this.Text = "Form1";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.Form1_FormClosed);
            this.Load += new System.EventHandler(this.Form1_Load);
            ((System.ComponentModel.ISupportInitialize)(this.trackBar_H)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBar1_W)).EndInit();
            this.groupBox1.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.objectInfoBindingSource)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.objectInfoBindingSource1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ListBox listBox1;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Button button3;
        private System.Windows.Forms.BindingSource objectInfoBindingSource;
        private System.Windows.Forms.BindingSource objectInfoBindingSource1;
        private System.Windows.Forms.ListView listView1;
        private System.Windows.Forms.ColumnHeader columnHeader2;
        private System.Windows.Forms.ColumnHeader columnHeader3;
        private System.Windows.Forms.TrackBar trackBar_H;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TrackBar trackBar1_W;
        private System.Windows.Forms.GroupBox groupBox1;
        private UserControl1 userControl_NP;
        private UserControl1 userControl_SP;
        private UserControl1 userControl_HP;
    }
}

