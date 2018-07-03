namespace Guagua
{
    class ReadData_from_Mem
    {
        public ProcessMemoryReader pmr = null;
        public int baseAddress = 0;
        public ReadData_from_Mem(uint nProcessID,int _baseAddress,int[]offset)
        {
            pmr = new ProcessMemoryReader();
            pmr.OpenProcess(nProcessID);

            baseAddress = pmr.ReadMultiLevelPointer(_baseAddress, 4, offset);
        }

        public byte[] ReadAMem(uint bytesToRead)
        {
            int nReadCount=0;
            return pmr.ReadtoMem(baseAddress, bytesToRead, out nReadCount);
        }
    }
}