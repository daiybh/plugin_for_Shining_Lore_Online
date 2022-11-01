using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;
using static System.Net.Mime.MediaTypeNames;

namespace Guagua
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
            while (!bExit)
            {
              //
                if (oi.enableWork)
                {
                    // 先来一次右键, 如果 sp 减少 说明 魔法发送了.
                    //就一直持续发送魔法,
                    //直到魔法不变
                    //捡东西

                    if (!oi.bFiexdAttack)
                    {
                        oi.pressAdd();
                        oi.pressZ();
                    }
                    oi.refeshObjInfo();

                    bool bHadAttack = false;
                    if (oi.bAttack)
                    {
                        var (b1,X1,Y1)= oi.testAttack();
                        if (b1)
                        {
                            oi.attack_begin(X1, Y1);
                            for (int i = 0; oi.isSPDecrease(); i++)
                            {
                                if (i % 10 == 0)
                                    oi.attack_begin(X1, Y1);
                                Thread.Sleep(10);
                                bHadAttack = true;
                            }
                            oi.attack_end(X1, Y1);
                        }
                    }
                    oi.testPickUp();
                   
                }
                Thread.Sleep(GolbalSetting.GetInstance().threadSleep);
            }
        }



        public void startWork()
        {
            t1 = new Thread(new ThreadStart(doWorkThread));
            t1.IsBackground = true;
            bExit = false;
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
