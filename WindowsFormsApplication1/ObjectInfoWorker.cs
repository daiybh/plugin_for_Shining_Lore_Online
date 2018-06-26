using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsApplication1
{
    class ObjectInfoWorker
    {
        private Thread t1 = null;
        private bool bExit = false;
        private ObjectInfo oi = null;
        public ObjectInfoWorker(ObjectInfo _oi, ManualResetEvent _autoEvent)
        {
            autoEvent = _autoEvent;
            this.oi = _oi;
        }
        ManualResetEvent autoEvent = null;
        public void doWorkThread()
        {
            int X = 0;
            int Y = 0;
            int leftMove = 100;
            int leftmoveCnt = 0;
            int[] narrX = new[] { +1, 0, -1, 0, +1, 0, -1, 0, +1, 0 };
            int[] narrY = new[] {  0, +1, 0, -1, 0, +1, 0, -1, 0,+1 };
            while (!bExit)
            {
                
                  if (oi.enableWork)
                 
                {
                    oi.pressAdd();
                    MouseEvent.pressKey(oi.hWnd, Keys.Z);
                }

                //RightAttack(center_X, center_y);
                
                for (int h = oi.Object_H * -1; h < 10; h += GolbalSetting.GetInstance().step_H)
                {
                    for (int w = oi.Object_W / 2 * -1; w < oi.Object_W / 2; w += GolbalSetting.GetInstance().step_W)
                    {
                        if (!oi.enableWork) continue;
                        X = oi.center_X + w;
                        Y = oi.center_y + h;
                        if (oi.enableWork)
                        {
                            oi.attack(X, Y);
                            oi.screenshotting();
                        }

                        autoEvent.WaitOne();
                    }
                }/**/

//                 int nOffsite = leftMove;
//                 int npos = leftmoveCnt % 10;
// 
//                 nOffsite = leftMove * narrX[npos];
// 
//                 oi.moveTo(oi.center_X + leftMove * narrX[npos], oi.center_y+ leftMove * narrY[npos]);
//                 Thread.Sleep(100);
//                 autoEvent.WaitOne();
//                 leftmoveCnt++;
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
    }
}
