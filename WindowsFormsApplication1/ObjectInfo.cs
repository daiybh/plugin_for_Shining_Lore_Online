﻿using System;
using System.Drawing;
using System.Runtime.InteropServices;
using System.Security.Cryptography;
using System.Threading;
using System.Windows.Forms;

namespace Guagua
{
    class ObjectInfo
    {
        private ObjecInfo_HP_SP_NP objeMem_HP_SP_NP = null;
        private ObjectInfo_JingYan objJingYan = null;
        private ObjectInfo_Money objectInfoMoney = null;
        public static string filterName = " 永恒天使 - ";
        public static int filterLength = filterName.Length;
        public int processID = 0;
        public ObjectInfo(IntPtr _hwnd, string title, MyFindWindow.RECT rt,int _processID)
        {
            this.hWnd = _hwnd;
            this.processID = _processID;
            this.title = title;
            this.enableWork = true;
            this.userName = title;// title.Substring(filterLength);
            this.rt = rt;
            center_X = (rt.Right - rt.Left) / 2;
            center_y = (rt.Bottom - rt.Top) / 2;
            if (rt.Height() < 700)
            {
                Object_H = 163;
                Object_W = 50;
            }
            objeMem_HP_SP_NP = new ObjecInfo_HP_SP_NP((uint)_processID);

            objJingYan = new ObjectInfo_JingYan((uint)_processID);

            objectInfoMoney = new ObjectInfo_Money((uint)_processID);
            refeshObjInfo();
        }

        public override string ToString()
        {
            return string.Format("hWnd:{0} title:{1}", this.hWnd, this.title);
        }

        public void setGraphics(Graphics _g)
        {
            g = _g;
        }
        public string userName { get; set; }
        public bool enableWork
        {
            get { return _enableWork; }
            set
            {
                _enableWork = value;
            }
        }
        private bool _fixedAttack=false;
        public bool bFiexdAttack
        {
            get { return _fixedAttack; }
            set
            {
                _fixedAttack = value;
                if (_fixedAttack)
                    bAttack = true;
            }
        }

        private bool _bAttack = false;
        public bool bAttack
        {
            get
            {
                return _bAttack;
            }
            set
            {
                _bAttack = value;
                if (!_bAttack)
                {
                    _fixedAttack = false;
                }
            }
        }
        public string currentHP
        {
            get { return string.Format("{0}/{1}", objeMem_HP_SP_NP.HP, objeMem_HP_SP_NP.HPMax); }
        }
        public string currentSP
        {
            get { return string.Format("{0}/{1}", objeMem_HP_SP_NP.sp, objeMem_HP_SP_NP.spMax); }
        }
        public string currentNP
        {
            get { return string.Format("{0}/{1}", objeMem_HP_SP_NP.np, objeMem_HP_SP_NP.npMax); }
        }
        public int NP
        {
            get { return objeMem_HP_SP_NP.np; }
        }

        public string CurrentMoney
        {
            get { return string.Format("钱:{0},经验:{1}/{2}",objectInfoMoney.money,objJingYan.Jingyan,objJingYan.JingyanMax); }
        }
        public bool bPickUP { get; set; } = true;
        private bool _bshowWindow = true;

        public bool bShowWindow
        {
            get { return _bshowWindow;}
            set
            {
                _bshowWindow = value;
                showWindow(value);
            }
        }

        private Graphics g;
        private IntPtr hWnd;
        private string title;
        public int center_X = 0;
        public int center_y = 0;
        public int Object_H = 247;
        public int Object_W = 76;
        public MyFindWindow.RECT rt;
        private bool _enableWork = false;
       
        
        public void showWindow(bool isShow)
        {
            _bshowWindow = isShow;
         MouseEvent.showWindow(this.hWnd,isShow);
        }
        
        private int offsetX = -100;
        int move_one_offset = 50;
        void move(IntPtr hWnd,int x,int y)
        {
            MouseEvent.moveMouse(hWnd, x, y);
            MouseEvent.Key_down(hWnd, Keys.Alt);
            MouseEvent.LeftClick(hWnd, x,y);
            MouseEvent.LeftClick(hWnd, x,y);
            MouseEvent.LeftClick(hWnd, x,y);
            MouseEvent.key_up(hWnd, Keys.Alt);
        }
        public void move_left_top_one()
        {
            int X = this.center_X - move_one_offset;
            int Y = this.center_y - move_one_offset;
            move(this.hWnd, X, Y);
        }

        public void move_left_down_one()
        {
            int X = this.center_X - move_one_offset;
            int Y = this.center_y + move_one_offset;
            move(this.hWnd, X, Y);
        }
        public void move_left_one()
        {
            int X = this.center_X - move_one_offset;
            int Y = this.center_y;
            move(this.hWnd, X, Y);
        }
        public void move_right_down_one()
        {
            int X = this.center_X + move_one_offset;
            int Y = this.center_y + move_one_offset;
            move(this.hWnd, X, Y);
        }
        public void move_right_top_one()
        {
            int X = this.center_X + move_one_offset;
            int Y = this.center_y - move_one_offset;
            move(this.hWnd, X, Y);
        }
       
        public void move_right_one()
        {
            int X = this.center_X + move_one_offset;
            int Y = this.center_y ;
            move(this.hWnd, X, Y);
        }


        public void move_top_one()
        {
            int X = this.center_X ;
            int Y = this.center_y -move_one_offset*3;
            move(this.hWnd, X, Y);
        }


        public void move_down_one()
        {
            int X = this.center_X ;
            int Y = this.center_y + move_one_offset;
            move(this.hWnd, X, Y);
        }
        public void attackCenter()
        {
            MouseEvent.RightClick(this.hWnd, center_X, center_y);

            MouseEvent.RightClick(this.hWnd, center_X, center_y);

            // Console.WriteLine($"{this.userName} attack>>{x} {y} ");
            //  Thread.Sleep(10);
        }
        public void testPickUp2()
        {

            //move up 10                    //move down 10
            //move left 10                    //move right 10
            //move down 10                    //move up 10
            //move right 10                    //move left 10
            for (int i = 0; i < 1000; i++)
            {
                MouseEvent.moveMouse(hWnd, center_X, center_y);
                int offset = 60;
                {
                    int X = this.center_X - offset;
                    int Y = this.center_y;// - offset;
                    MouseEvent.moveMouse(hWnd, X, Y);
                    MouseEvent.Key_down(hWnd, Keys.Alt);
                    pickUP(X, Y);

                    MouseEvent.key_up(hWnd, Keys.Alt);
                }
                {
                    MouseEvent.moveMouse(hWnd, center_X, center_y);
                    int X = this.center_X + offset;;
                    int Y = this.center_y;// + offset/3 ;

                    MouseEvent.moveMouse(hWnd, X, Y);
                    MouseEvent.Key_down(hWnd, Keys.Alt);
                    pickUP(X, Y);

                    MouseEvent.key_up(hWnd, Keys.Alt);
                }
            }

        }
        public void testPickUp()
        {
            for (int i = 0; i < 4; i++)
            {
                if (!bPickUP) return;
               // pressZ();

                MouseEvent.Key_down(hWnd, Keys.Alt);
                for (int h = this.Object_H * -1; h < 20; h += GolbalSetting.GetInstance().step_H)
                {
                    if (!bPickUP) break;
                    for (int w = this.Object_W / 2 * -1; w < this.Object_W ; w += GolbalSetting.GetInstance().step_W)
                    {
                        if (!bPickUP) break;
                        int X = this.center_X + w;
                        int Y = this.center_y + h;

                        pickUP(X, Y);

                    }
                }
                MouseEvent.key_up(hWnd, Keys.Alt);
            }
        }
        public Tuple<bool,int,int> testAttack()
        {
            objeMem_HP_SP_NP.doRead();
            int beginSP = objeMem_HP_SP_NP.sp;
            if(_fixedAttack)
            {
                int X = center_X;
                int Y = center_y-50;
                this.attack_begin(X,Y);
                Thread.Sleep(100);
                objeMem_HP_SP_NP.doRead();
                int curSP = objeMem_HP_SP_NP.sp;
                this.attack_end(X, Y);
                return new Tuple<bool, int, int>(beginSP != curSP, X, Y);

            }
            for (int h = this.Object_H * -1; h < 20; h += GolbalSetting.GetInstance().step_H)
            {
                for (int w = this.Object_W / 2 * -1; w < this.Object_W *2; w += GolbalSetting.GetInstance().step_W)
                {
                    if (!this.enableWork) continue;
                    int X = this.center_X + w;
                    int Y = this.center_y + h;
                    if (this.enableWork)
                    {
                        // oi.attack(X, Y);
                        // oi.screenshotting();
                        this.attack_begin(X, Y);
                        Thread.Sleep(10);
                        objeMem_HP_SP_NP.doRead();
                        this.attack_end(X, Y);
                        int curSP = objeMem_HP_SP_NP.sp;
                        Console.WriteLine($"{this.userName} testAttack>>{h} {w} {X} {Y} {beginSP} {curSP}");
                        if (beginSP!=curSP)
                        {
                            return new Tuple<bool, int, int>( true,X,Y);
                        }
                    }
                }
            }

            return new Tuple<bool, int, int>(false,0,0);
        }
        public void attack_begin(int x=0,int y=0)
        {
            if (x == 0 && y == 0)
            {
                x = this.center_X + 10;
                y = this.center_y - 100;
            }
            MouseEvent.Right_down(this.hWnd,x,y);
            Console.WriteLine($"{this.userName} attack_begin>>{x} {y} ");
        }
        public void attack_end(int x = 0, int y = 0)
        {
            if (x == 0 && y == 0)
            {
                x = this.center_X + 10;
                y = this.center_y - 100;
            }

            MouseEvent.Right_up(this.hWnd, x, y);
            Console.WriteLine($"{this.userName} attack_end>>{x} {y} ");
        }
        public void attack(int x, int y)
        {
            //  RightAttack(x, y);
            if (!bAttack)
                return;
            MouseEvent.RightClick(this.hWnd, x, y);

            MouseEvent.RightClick(this.hWnd, x, y);

            // Console.WriteLine($"{this.userName} attack>>{x} {y} ");
            //  Thread.Sleep(10);
        }
        public void pickUP(int x,int y)
        {
            if (bPickUP)
                MouseEvent.LeftClick(this.hWnd, x, y);
            Console.WriteLine($"{this.userName} pickUP>>{x} {y} ");
        }

        private bool bPressAdd = false;
        public void pressAdd()
        {
            if (bPressAdd) return;
            bPressAdd = true;
            //发送键盘按键 +
            for (int i = 0; i < 10; i++)
            {
                MouseEvent.moveMouse(hWnd, center_X + i * 10, center_y + i * 10);
                MouseEvent.pressKey(hWnd, Keys.Add);
                Thread.Sleep(1000);
            }
        }
        public void pressZ()
        {
            MouseEvent.pressKey(hWnd, Keys.Z);
        }

        [DllImport("user32.dll", SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        static extern bool PrintWindow(IntPtr hwnd, IntPtr hDC, uint nFlags);


        private Bitmap bmp = null;
        Graphics memoryGraphics = null;
        private IntPtr dc;
        private int lastUpdateTime = 0;
        int lastSP = 0;
        int lastAttackTime = 0;
        public bool isSPDecrease()
        {
            objeMem_HP_SP_NP.doRead();

            bool b =  lastSP > objeMem_HP_SP_NP.sp;
            if (objeMem_HP_SP_NP.sp == objeMem_HP_SP_NP.spMax) b = false;

            b = objeMem_HP_SP_NP.sp != objeMem_HP_SP_NP.spMax;
            Console.WriteLine($"{this.userName} isSPDecrease>>{b} {lastSP} {objeMem_HP_SP_NP.sp} {objeMem_HP_SP_NP.spMax} ");

            lastSP = objeMem_HP_SP_NP.sp;
            if(b)
                lastAttackTime = System.Environment.TickCount & Int32.MaxValue;

            return b;
        }
        public bool canPickUP()
        {
            if (!bPickUP) return false;
            if (isSPDecrease()) return false;
            int curTime = System.Environment.TickCount & Int32.MaxValue;
            if (lastAttackTime!=0 && curTime - lastAttackTime > 2000) return false;
            return true;

        }

        public void refeshObjInfo()
        {
            objeMem_HP_SP_NP.doRead();
            objectInfoMoney.doRead();
            objJingYan.doRead();
            if (GolbalSetting.GetInstance().HPPercent * objeMem_HP_SP_NP.HPMax / 10 > objeMem_HP_SP_NP.HP)
            {
                Console.WriteLine("{0}>>life:{1} {2} ", this.userName, objeMem_HP_SP_NP.HP,objeMem_HP_SP_NP.HPMax);
                increaseHP();
            }

            if (GolbalSetting.GetInstance().SPPercent * objeMem_HP_SP_NP.spMax / 10 > objeMem_HP_SP_NP.sp)
            {
                Console.WriteLine("{0}>>sp:{1} {2} ", this.userName, objeMem_HP_SP_NP.sp, objeMem_HP_SP_NP.spMax);
                increaseSP();
            }

            if (GolbalSetting.GetInstance().NPPercent * objeMem_HP_SP_NP.npMax / 10 > objeMem_HP_SP_NP.np)
            {
                Console.WriteLine("{0}>>NP:{1} {2} ", this.userName, objeMem_HP_SP_NP.np, objeMem_HP_SP_NP.npMax);
                increaseNP();
            }
        }

        public void increaseHP()
        {
            //喝血
            if (GolbalSetting.GetInstance().keyPress_HP[0])
            {
                for (int i = 0; i < 5; i++)
                {
                    if (GolbalSetting.GetInstance().keyPress_HP[i + 1])
                    {
                        MouseEvent.pressKey(hWnd, Keys.D1 + i);
                        break;
                    }
                }
            }
        }
        public void increaseSP()
        {
            //喝血
            // MouseEvent.pressKey(hWnd, Keys.D0);
            if (GolbalSetting.GetInstance().keyPress_SP[0])
            {
                for (int i = 0; i < 5; i++)
                {
                    if (GolbalSetting.GetInstance().keyPress_SP[i + 1])
                    {
                        MouseEvent.pressKey(hWnd, Keys.D1 + i);
                        break;
                    }
                }
            }
        }
        public void increaseNP()
        {
            //喝血
            //   MouseEvent.pressKey(hWnd, Keys.D0);
            if (GolbalSetting.GetInstance().keyPress_NP[0])
            {
                for (int i = 0; i < 5; i++)
                {
                    if (GolbalSetting.GetInstance().keyPress_NP[i + 1])
                    {
                        MouseEvent.pressKey(hWnd, Keys.D1 + i);
                        break;
                    }
                }
            }
        }
        public void screenshotting()
        {
            int curTime = System.Environment.TickCount & Int32.MaxValue;
            if (curTime - lastUpdateTime < 2000) return;
            lastUpdateTime = curTime;

            if (bmp == null)
            {
                bmp = new Bitmap(this.rt.Width(), this.rt.Height(), g);
                memoryGraphics = Graphics.FromImage(bmp);
                //  dc = memoryGraphics.GetHdc();
            }

            dc = memoryGraphics.GetHdc();
            bool success = PrintWindow(this.hWnd, dc, 0);
            memoryGraphics.ReleaseHdc(dc);
            // bmp now contains the screenshot
            //  bmp.Save("c:\\jpeg\\ccccc.jpg");
            float a = 0.6F;

            int hh = 63;
            int firstLine = this.rt.Height()-96;

            //14,701 33,763
            //52,701 63,763
            //81,701 92,763
            a = (10 - (GolbalSetting.GetInstance().HPPercent + 1))/10.0F;
            Color colorHP = bmp.GetPixel(22, Convert.ToInt32(hh * a + firstLine)); //判断 Color.B 是否为0 


            if (colorHP.B != 0)
            {
               
                increaseHP();
                Console.WriteLine("{0},{1}>>life:{1} ", this.userName, a, colorHP.ToString());
            }

            a = (10 - (GolbalSetting.GetInstance().SPPercent + 1)) / 10.0F;
            Color colorSP = bmp.GetPixel(60, Convert.ToInt32(hh * a + firstLine)); //判断 Color.G 是否为0 


            if (colorSP.G != 0)
            {
              
                increaseSP();
                Console.WriteLine("{0},{1}>>tec:{1} ", this.userName, a, colorSP.ToString());
            }

            a = (10 - (GolbalSetting.GetInstance().NPPercent + 1)) / 10.0F;
            Color colorNP = bmp.GetPixel(88, Convert.ToInt32(hh * a + firstLine)); //判断 Color.B 是否为0
            if (colorNP.B != 0)
            {
               increaseNP();
                Console.WriteLine("{0},{1}>>cPower:{2} ", this.userName,a, colorNP.ToString());
            }


            Console.WriteLine("{3}>>colorHP:{0} colorSP:{1} colorNP:{2}", colorHP.ToString(), colorSP.ToString(), colorNP.ToString(), a);
        }

      
    }
}
