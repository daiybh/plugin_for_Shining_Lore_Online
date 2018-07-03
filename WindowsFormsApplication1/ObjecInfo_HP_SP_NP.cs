using System;

namespace WindowsFormsApplication1
{
    abstract class ObjectInfoFromMem_base
    {
        public ReadData_from_Mem objeInMem;
        private uint nProcessID = 0;

        
        public ObjectInfoFromMem_base(uint nProcessID,int baseAddress,int[]offset)
        {
            this.nProcessID = nProcessID;
            objeInMem = new ReadData_from_Mem(nProcessID, baseAddress,offset);
        }

        abstract public void doRead();
    }
    class ObjecInfo_HP_SP_NP: ObjectInfoFromMem_base
    {
        public ObjecInfo_HP_SP_NP(uint nProcessID):base(nProcessID, 0x009C98BC, new[] { 0x464, 0x604 })
        {
        }
        public int HP;
        public int HPMax;
        public int sp;
        public int spMax;
        public int np;
        public int npMax;
        public override void doRead()
        {
            byte[] bReaded = objeInMem.ReadAMem(28);
            
            HP = BitConverter.ToInt32(bReaded, 0);
            HPMax = BitConverter.ToInt32(bReaded, 4);
            sp = BitConverter.ToInt32(bReaded, 8);
            spMax = BitConverter.ToInt32(bReaded, 12);
            np = BitConverter.ToInt32(bReaded, 16);
            npMax = BitConverter.ToInt32(bReaded, 20);
        }
    }

    class ObjectInfo_JingYan : ObjectInfoFromMem_base
    {
        public int Jingyan;
        public int JingyanMax;
        public ObjectInfo_JingYan(uint nProcessID) : base(nProcessID, 0x0099C134, new[] { 0x154,0x130-8 })
        {
        }

        public override void doRead()
        {
            byte[] bRead = objeInMem.ReadAMem(12);
            JingyanMax = BitConverter.ToInt32(bRead, 0);
            Jingyan = BitConverter.ToInt32(bRead, 8);
        }
    }
    class ObjectInfo_Money : ObjectInfoFromMem_base
    {
        public int money;
        public int JingyanMax;
        public ObjectInfo_Money(uint nProcessID) : base(nProcessID, 0x0099C134, new[] { 0x358, 0x8, 0x168 })
        {
        }

        public override void doRead()
        {
            byte[] bRead = objeInMem.ReadAMem(4);
            money = BitConverter.ToInt32(bRead, 0);
        }
    }
}