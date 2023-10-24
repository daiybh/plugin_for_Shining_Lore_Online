#pragma once
#include <vector>

class MemBase {
public :
	MemBase(){}
	void open(int pid)
	{
		m_nProcessID = pid;
		if (m_hProcess != nullptr) CloseHandle(m_hProcess);
		m_hProcess = OpenProcess(PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION,
			1, m_nProcessID);
	}
	DWORD readMem(int address,int offset, void* buffer, int size)
	{
		if (m_hProcess == NULL)
			return 0;

		DWORD dwNumberOfBytesRead;
		int baseAddress;
		ReadProcessMemory(m_hProcess, (LPCVOID)address, &baseAddress, 4, &dwNumberOfBytesRead);
		int newAddress = baseAddress + offset;

		ReadProcessMemory(m_hProcess, (LPCVOID)newAddress, buffer, size, &dwNumberOfBytesRead);

		return dwNumberOfBytesRead;
	}
	
	virtual void doRead()=0;
protected:

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
	
	struct ObjPos {
		float x = 0;
		float y = 0;
		int z = 0;
		int w = 0;
	};
	ObjPos bb1;
	void getGPS(int& x, int& y)
	{
		readMem(0x0099c134, (0x0400E0c8 - 0x0400df00), &bb1, sizeof(bb1));
		x = (int)bb1.x / 10;
		y = (int)bb1.y / 10;		
	}
	struct Info {
		int HP = 0;
		int HPMax = 0;
		int sp = 0;
		int spMax = 0;
		int np = 0;
		int npMax = 0;
	};
	Info info;
	void getHP()
	{
		readMem(0X009C98BC, (0x3f8ab4c - 0x3f88e90), &info, sizeof(info));
	}
	void doRead() {
		getHP();		
	}
};