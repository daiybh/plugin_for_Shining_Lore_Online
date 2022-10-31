using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

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
                Thread.Sleep(GolbalSetting.GetInstance().threadSleep);
                if (oi.enableWork)
                {
                    // 先来一次右键, 如果 sp 减少 说明 魔法发送了.
                    //就一直持续发送魔法,
                    //直到魔法不变
                    //捡东西
                    oi.refeshObjInfo();

                    bool bHadAttack = false;
                    if (oi.bAttack)
                    {

                        oi.attack_begin();
                        for (int i = 0; oi.isSPDecrease(); i++)
                        {
                            if (i % 10 == 0)

                                oi.attack_begin();
                            Thread.Sleep(10);
                            bHadAttack = true;
                        }
                        oi.attack_end();
                    }
                    if (oi.bPickUP && bHadAttack)
                    {
                        oi.pressAdd();
                        oi.pressZ();
                        for (int h = oi.Object_H * -1; h < 10; h += GolbalSetting.GetInstance().step_H)
                        {
                            for (int w = oi.Object_W / 2 * -1; w < oi.Object_W / 2; w += GolbalSetting.GetInstance().step_W)
                            {
                                if (!oi.enableWork) continue;
                                X = oi.center_X + w;
                                Y = oi.center_y + h;
                                if (oi.enableWork)
                                {
                                    // oi.attack(X, Y);
                                    // oi.screenshotting();
                                    oi.pickUP(X, Y);
                                }
                            }
                        }
                    }
                }
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
