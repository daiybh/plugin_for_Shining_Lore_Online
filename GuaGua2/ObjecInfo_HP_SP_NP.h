#pragma once
#include <vector>

class MemBase {
public :
	MemBase(){}
	void GetBaseAddress(int pid,int baseAddress, const std::vector< int> &offset) {
		m_nProcessID = pid;
		m_baseAddress = ReadMultiLevelPointer(baseAddress,4,offset);
	}
	int  ReadAMem(int *bufferDest,int bufferSize)
	{
		return ReadtoMem(m_baseAddress, bufferDest, bufferSize);
	}
	void getGPS( int &x,int &y)
	{		
		float fx=0, fy=0;
		int tmp;
		DWORD dwNumberOfBytesRead;
		if (m_hProcess != NULL)
		{
			ReadProcessMemory(m_hProcess, (LPCVOID)0x0099c134, &tmp, 4, &dwNumberOfBytesRead);
			//tmp = 0x03f287b8
			int Xoffset = 0x03f2899c - 0x03f287b8;
			int newXOffset = tmp + Xoffset;
			///x
			ReadProcessMemory(m_hProcess, (LPCVOID)newXOffset, &fx, 4, &dwNumberOfBytesRead);


			int Yoffset = 0x03f28984 - 0x03f287b8;
			int newYOffset = tmp + Yoffset;
			///y
			ReadProcessMemory(m_hProcess, (LPCVOID)newYOffset, &fy, 4, &dwNumberOfBytesRead);

		}
		x = (int)fx/100;
		y = (int)fy/100;
	}
	virtual void doRead()=0;
protected:

	int ReadMultiLevelPointer(int _baseAddress, int byteToRead, const std::vector< int>& offsetArr)
	{
		checkBuffer(byteToRead);
		if (m_hProcess != nullptr) CloseHandle(m_hProcess);
		m_hProcess = OpenProcess(PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION,
			1, m_nProcessID);
		if (m_hProcess == NULL)return 0;
		
		int pAddress = _baseAddress;
		for (int i = 0; i < offsetArr.size(); i++)
		{
			if (i == 0)
			{
				ReadProcessMemory(m_hProcess, (LPVOID)pAddress, m_byteReadBuffer, byteToRead, NULL);
			}
			pAddress = *(m_byteReadBuffer)+offsetArr[i];

			ReadProcessMemory(m_hProcess, (LPVOID)(pAddress), m_byteReadBuffer, byteToRead, NULL);
		}
		return pAddress;
	}
	int ReadtoMem(int MemoryAddress, int *bufferToRead, int bufferSize)
	{
		if (m_hProcess == nullptr)return 0;
		SIZE_T bytesReaded = 0;
		ReadProcessMemory(m_hProcess, (LPVOID)MemoryAddress, bufferToRead, bufferSize,&bytesReaded);
		return bytesReaded;
	}
	void checkBuffer(int bytesToRead)
	{
		if (bytesToRead > m_byteBufferSize)
		{
			if (m_byteReadBuffer != NULL)
				delete[] m_byteReadBuffer;
			m_byteReadBuffer = new int[bytesToRead];
		}
	}
	int *m_byteReadBuffer=nullptr;
	int m_byteBufferSize = 0;
	int m_baseAddress=0;
	int m_nProcessID;
protected:
	HANDLE m_hProcess = NULL;
};
class ObjecInfo_HP_SP_NP:public MemBase {
public:
	ObjecInfo_HP_SP_NP() {}
	void open(int nProcessID)
	{
		const  std::vector<int> offset = { 0x464,0x604 };
		GetBaseAddress(nProcessID, 0X009C98BC, offset);
	}

	
	struct Info{
	 int HP=0;
	 int HPMax = 0;
	 int sp = 0;
	 int spMax = 0;
	 int np = 0;
	 int npMax = 0;
	};
	Info info;
	
	void doRead() {
		ReadAMem((int*) & info, sizeof(info));
	};
};