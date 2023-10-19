#pragma once
#include <Windows.h>  
#include <tchar.h>
#include <tlhelp32.h>  
#include <iostream>  

#pragma comment(lib, "Kernel32.lib")  
class Sharemem {

public:
	int CreateSharemem(DWORD processId)
	{
		// ��ȡ��ǰ����ID  

		TCHAR sharedMemName[256];
		_stprintf_s(sharedMemName,_T("SharedMem-%d"), processId);
		//std::string sharedMemName = ("SharedMem-" + std::to_string(processId));  // �滻Ϊʵ�ʵĹ����ڴ�����  


		// �򿪹����ڴ����  
		HANDLE sharedMem = OpenFileMapping(
			FILE_MAP_READ | FILE_MAP_WRITE,   // ��/д����Ȩ��  
			FALSE,                            // ���̳о��  
			sharedMemName                    // ��������  
		);

		if (sharedMem == NULL) {
			// �����Խ���IDΪ���ƵĹ����ڴ����  
			sharedMem = CreateFileMapping(
				INVALID_HANDLE_VALUE,    // ʹ��Ĭ�ϵİ�ȫ������  
				NULL,                   // ���̳о��  
				PAGE_READWRITE,         // ��/д����Ȩ��  
				0,                      // �������С (0 = ʹ��ϵͳĬ��ֵ)  
				sizeof(int),            // ��������С  
				sharedMemName          // ��������  
			);

			if (sharedMem == NULL) {
				std::cout << "Failed to create shared memory object." << std::endl;
				OutputDebugString(_T("Failed to create shared memory object"));
				return 1;
			}
		}

		// �򿪹����ڴ�ӳ����ͼ  
		pView = MapViewOfFile(
			sharedMem,               // �����ڴ������  
			FILE_MAP_WRITE,          // д����Ȩ��  
			0,                       // ƫ���� (ͨ��Ϊ 0)  
			0,                       // Ҫӳ����ֽ��� (ͨ��Ϊ�����С)  
			NULL                     // ����ȷ��ӳ����ͼ��ַ�Ŀ�ѡ����  
		);

		if (pView == NULL) {
			std::cout << "Failed to map view of shared memory." << std::endl;
			OutputDebugString(_T("Failed to map view of shared memory."));
			CloseHandle(sharedMem);  // �رչ����ڴ������  
			sharedMem = nullptr;
			return 1;
		}
		return 0;

	}

	int getData() {
		// ��ȡ�����ڴ��еĵ�һ������ָ��  
		int* pSharedData = static_cast<int*>(pView);
		return *pSharedData;
	}

	void writeData(int iData)
	{
		TCHAR sz[256] = { 0 };
		_stprintf_s(sz,_T("writeData %d"), iData);
		OutputDebugString(sz);
		int* pSharedData = static_cast<int*>(pView);
		// �ڹ����ڴ���д������  
		*pSharedData = iData;  // ���磬д������ 42  
	}

		// �ڴ˴�����ִ�������������������̿���ͨ������ͬ�Ĺ����ڴ��������ȡ��д������  
	~Sharemem(){
		// ���ӳ����ͼ���رչ����ڴ������  
		if(pView)
			UnmapViewOfFile(pView);
		if(sharedMem)
			CloseHandle(sharedMem);
	}
	HANDLE sharedMem=nullptr;
	LPVOID pView=nullptr;
};