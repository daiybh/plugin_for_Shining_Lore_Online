#include <windows.h>
#include <detours.h>
#include <iostream>
#include <sstream>

#include "sharemem.h"
Sharemem* g_Sharemem = nullptr;
int g_count = 0;
// 获取当前窗口的句柄  
HWND GetCurrentWindowHandle()
{
	// 获取当前线程的窗口句柄  
	HWND hWnd = GetForegroundWindow();
	return hWnd;
}
//
//// 获取当前窗口的名称  
//LPCTSTR GetCurrentWindowName()
//{
//	HWND hWnd = GetCurrentWindowHandle();
//
//	// 获取窗口的标题文本长度  
//	int length = GetWindowTextLength(hWnd);
//
//	// 分配用于存储窗口标题文本的缓冲区  
//	TCHAR* buffer = new TCHAR[length + 1];
//
//	// 获取窗口的标题文本  
//	GetWindowText(hWnd, buffer, length + 1);
//	TCHAR szstr[256];
//	wsprintf(szstr, "GetCurrentWindowName %d (%s)  %x %d", g_count, buffer, (int)hWnd, GetCurrentProcessId());
//	OutputDebugStringA(szstr);
//	OutputDebugString(buffer);
//	return buffer;
//}




int (WINAPI* pMessageBoxA)(HWND hWnd, LPCSTR lpText, LPCSTR lpCaption, UINT uType) = ::MessageBoxA;

int WINAPI my_MessageBoxA(
	_In_opt_ HWND hWnd,
	_In_opt_ LPCSTR lpText,
	_In_opt_ LPCSTR lpCaption,
	_In_ UINT uType)
{
	//Log Debug String:
	{
		std::stringstream ss;
		ss << "Intercepted: " << __FUNCTION__ << " : " << lpCaption << " : " << lpText;
		OutputDebugStringA(ss.str().c_str());
	}

	std::stringstream ss;
	ss << "Intercepted: " << lpCaption;

	// Execute the normal function:
	return pMessageBoxA(hWnd, lpText, ss.str().c_str(), uType);
}
DWORD(WINAPI* pGetTickCount)(VOID) = GetTickCount;

DWORD
WINAPI
My_GetTickCount(
	VOID
)
{
	DWORD dw = pGetTickCount();

	return dw / 1000;
}

SHORT(WINAPI* pGetAsyncKeyState)(_In_ int vKey) = GetAsyncKeyState;

SHORT
WINAPI
My_GetAsyncKeyState(
	_In_ int vKey)
{
	g_count++;
	SHORT x = pGetAsyncKeyState(vKey);

	if (vKey == 0x12)
	{	
		if (g_Sharemem)
		{
			int a = g_Sharemem->getData();
			if (a == 1)
				return 0xffff8001;
		}
		else {
			char szstr[256];
			sprintf_s(szstr, "%d My_GetAsyncKeyState (key:%x)=%x g_Sharemem ==null", g_count, vKey, x);
			OutputDebugStringA(szstr);
		}

	}
	return x;
}



void hook_api(bool enable)
{
	LONG(WINAPI * _DetourAction)(_Inout_ PVOID * ppPointer, _In_ PVOID pDetour) = NULL;
	if (enable) {
		_DetourAction = DetourAttach;
	}
	else {
		_DetourAction = DetourDetach;
	}

	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());

	// perform the action (hooking/unhooking):
   // _DetourAction(&(PVOID&)pMessageBoxA, my_MessageBoxA);

   // _DetourAction(&(PVOID&)pGetTickCount, My_GetTickCount);
	_DetourAction(&(PVOID&)pGetAsyncKeyState, My_GetAsyncKeyState);


	DetourTransactionCommit();
}
//创建以当前 processId 为名字的 sharemem
//用第一个Int 作为变量 还获取是否alt 被按下

BOOL WINAPI DllMain(HANDLE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		OutputDebugStringA("Hooking the process");
		{
			TCHAR szstr[256];
			HWND hWnd = GetCurrentWindowHandle();
			wsprintf(szstr, "DllMain %d   %x %d", g_count, (int)hWnd, GetCurrentProcessId());
			OutputDebugStringA(szstr);
		}
		g_Sharemem = new Sharemem();
		g_Sharemem->CreateSharemem(GetCurrentProcessId());
		hook_api(true);
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		OutputDebugStringA("Unhooking the process");
		hook_api(false);
		delete g_Sharemem;
		g_Sharemem = nullptr;
		break;
	}
	return TRUE;
}
