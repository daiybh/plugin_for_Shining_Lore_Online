﻿
// GuaGua2.cpp: 定义应用程序的类行为。
//

#include "pch.h"
#include "framework.h"
#include "GuaGua2.h"
#include "GuaGua2Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGuaGua2App

BEGIN_MESSAGE_MAP(CGuaGua2App, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CGuaGua2App 构造

CGuaGua2App::CGuaGua2App()
{
	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的 CGuaGua2App 对象

CGuaGua2App theApp;


// CGuaGua2App 初始化
#include <string>
#include <corecrt_wstring.h>
BOOL CGuaGua2App::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。  否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();


	TCHAR windowTitle[256];

	if(0)
	{
		HWND hWndp = FindWindowEx(NULL, NULL, L"Notepad", NULL);
		
		HWND hWnd = FindWindowEx(hWndp, nullptr, L"RichEditD2DPT", nullptr);

		::GetWindowText(hWnd, windowTitle, sizeof(windowTitle));
		Sleep(1000);
		hWnd = (HWND)0x00090790;
		PostMessage(hWnd, WM_CHAR, 'u', 0);

		UINT VirtualKey = MapVirtualKey(VK_RIGHT, 0);
		PostMessage(hWnd, WM_KEYDOWN, VK_RIGHT, 0x0001 | VirtualKey << 16);
		PostMessage(hWnd, WM_KEYUP, VK_RIGHT, 0x0001 | VirtualKey << 16 | 0xC0 << 24);
		//Sleep(1000);
		//CString xt = windowTitle;
		//AfxMessageBox(xt);
		//::SetForegroundWindow(hWnd);
		//Sleep(1000);
		//keybd_event(VK_MENU, MapVirtualKey(VK_MENU, 0), 0, 0);
		//Sleep(1000);
		//keybd_event('D', MapVirtualKey('D', 0), 0, 0);
		//Sleep(1000);
		//
		//keybd_event(VK_MENU,MapVirtualKey(VK_MENU,0),KEYEVENTF_KEYUP,0);
		//Sleep(1000);
		//keybd_event('F', MapVirtualKey('F', 0), 0, 0);
		Sleep(1000);

		PostMessage(hWndp, WM_SYSKEYDOWN, VK_F4, 0x003E0001 | 0x20000000);
		PostMessage(hWndp, WM_SYSKEYUP, VK_F4, 0xC03E0001 | 0x20000000);
		exit(0);
	}
	if (0)
	{
		HWND hWnd = FindWindowEx(NULL, NULL, L"EVERYTHING", NULL);
		if (hWnd != NULL)
		{
			hWnd = FindWindowEx( nullptr, hWnd, L"Edit", NULL);

			::GetWindowText(hWnd, windowTitle, sizeof(windowTitle));
			CString xt = windowTitle;
			AfxMessageBox(xt);
			PostMessage(hWnd, WM_CHAR, 'a', 0);
			Sleep(1000);
			LPARAM lParam = MAKELPARAM(MK_ALT, 'D');
			LRESULT lr1,lr2,lr3;
			lr1 = SendMessage(hWnd, WM_SYSKEYDOWN, VK_MENU, lParam);
			Sleep(1000);
			lr2 = SendMessage(hWnd, WM_SYSKEYDOWN, 'D', lParam);
			Sleep(1000);
			lr3 = SendMessage(hWnd, WM_SYSKEYUP, VK_MENU, lParam);
			Sleep(1000);

			CString xx;
			xx.Format(L"%x %x %x", lr1, lr2, lr3);
			AfxMessageBox(xx);
		}
		exit(0);
	}
	// 创建 shell 管理器，以防对话框包含
	// 任何 shell 树视图控件或 shell 列表视图控件。
	CShellManager *pShellManager = new CShellManager;

	// 激活“Windows Native”视觉管理器，以便在 MFC 控件中启用主题
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));

	CGuaGua2Dlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 在此放置处理何时用
		//  “确定”来关闭对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 在此放置处理何时用
		//  “取消”来关闭对话框的代码
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "警告: 对话框创建失败，应用程序将意外终止。\n");
		TRACE(traceAppMsg, 0, "警告: 如果您在对话框上使用 MFC 控件，则无法 #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS。\n");
	}

	// 删除上面创建的 shell 管理器。
	if (pShellManager != nullptr)
	{
		delete pShellManager;
	}

#if !defined(_AFXDLL) && !defined(_AFX_NO_MFC_CONTROLS_IN_DIALOGS)
	ControlBarCleanUp();
#endif

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
	return FALSE;
}

