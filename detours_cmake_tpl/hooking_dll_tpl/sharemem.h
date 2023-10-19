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
		// 获取当前进程ID  

		TCHAR sharedMemName[256];
		_stprintf_s(sharedMemName,_T("SharedMem-%d"), processId);
		//std::string sharedMemName = ("SharedMem-" + std::to_string(processId));  // 替换为实际的共享内存名称  


		// 打开共享内存对象  
		HANDLE sharedMem = OpenFileMapping(
			FILE_MAP_READ | FILE_MAP_WRITE,   // 读/写访问权限  
			FALSE,                            // 不继承句柄  
			sharedMemName                    // 对象名称  
		);

		if (sharedMem == NULL) {
			// 创建以进程ID为名称的共享内存对象  
			sharedMem = CreateFileMapping(
				INVALID_HANDLE_VALUE,    // 使用默认的安全描述符  
				NULL,                   // 不继承句柄  
				PAGE_READWRITE,         // 读/写访问权限  
				0,                      // 最大对象大小 (0 = 使用系统默认值)  
				sizeof(int),            // 缓冲区大小  
				sharedMemName          // 对象名称  
			);

			if (sharedMem == NULL) {
				std::cout << "Failed to create shared memory object." << std::endl;
				OutputDebugString(_T("Failed to create shared memory object"));
				return 1;
			}
		}

		// 打开共享内存映射视图  
		pView = MapViewOfFile(
			sharedMem,               // 共享内存对象句柄  
			FILE_MAP_WRITE,          // 写访问权限  
			0,                       // 偏移量 (通常为 0)  
			0,                       // 要映射的字节数 (通常为对象大小)  
			NULL                     // 用于确定映射视图地址的可选参数  
		);

		if (pView == NULL) {
			std::cout << "Failed to map view of shared memory." << std::endl;
			OutputDebugString(_T("Failed to map view of shared memory."));
			CloseHandle(sharedMem);  // 关闭共享内存对象句柄  
			sharedMem = nullptr;
			return 1;
		}
		return 0;

	}

	int getData() {
		// 获取共享内存中的第一个整数指针  
		int* pSharedData = static_cast<int*>(pView);
		return *pSharedData;
	}

	void writeData(int iData)
	{
		TCHAR sz[256] = { 0 };
		_stprintf_s(sz,_T("writeData %d"), iData);
		OutputDebugString(sz);
		int* pSharedData = static_cast<int*>(pView);
		// 在共享内存中写入数据  
		*pSharedData = iData;  // 例如，写入数字 42  
	}

		// 在此处可以执行其他操作，其他进程可以通过打开相同的共享内存对象来读取或写入数据  
	~Sharemem(){
		// 解除映射视图并关闭共享内存对象句柄  
		if(pView)
			UnmapViewOfFile(pView);
		if(sharedMem)
			CloseHandle(sharedMem);
	}
	HANDLE sharedMem=nullptr;
	LPVOID pView=nullptr;
};