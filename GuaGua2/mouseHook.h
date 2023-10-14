#pragma once
#include <windows.h>

HHOOK mouse_Hook;
LRESULT CALLBACK LowLevelMouseProc(INT nCode,
	WPARAM wParam,
	LPARAM lParam
);
BOOL UninstallHook();  //ж��  
BOOL InstallHook();     //��װ
// CGuaGua2App ��ʼ��
#include <string>
#include <corecrt_wstring.h>
#include <atltypes.h>
#include <atlstr.h>
BOOL InstallKbHook(HINSTANCE hInstance)
{

	if (mouse_Hook)   UninstallHook();
	mouse_Hook = SetWindowsHookEx(WH_MOUSE_LL,
		(HOOKPROC)(LowLevelMouseProc),hInstance, NULL);

	return(mouse_Hook != NULL);
}

BOOL UninstallHook()
{

	BOOL jud = FALSE;
	if (mouse_Hook) {
		jud = UnhookWindowsHookEx(mouse_Hook);
		mouse_Hook = NULL;  //set NULL  

	}

	return jud;
}
bool bStartLog = false;
CPoint lastPoint;
LRESULT CALLBACK LowLevelMouseProc(INT nCode, WPARAM wParam, LPARAM lParam)
{
	CPoint  _mousepoint;
	MSLLHOOKSTRUCT* pkbhs = (MSLLHOOKSTRUCT*)lParam;
	switch (nCode)
	{

	case HC_ACTION:
	{
		if (wParam == WM_MOUSEMOVE)
		{
			GetCursorPos(&_mousepoint);
			CString x;
			x.Format(L"_mousepointMMM x[%d-%d=%2d] y[%d-%d=%2d]",
				_mousepoint.x, lastPoint.x, _mousepoint.x - lastPoint.x,
				_mousepoint.y, lastPoint.y, _mousepoint.y - lastPoint.y);
			OutputDebugString(x);
		}
		if (wParam == WM_RBUTTONUP)
		{
			bStartLog = !bStartLog;
			break;
		}
		if (bStartLog && wParam == WM_LBUTTONUP)
		{
			GetCursorPos(&_mousepoint);
			CString x;
			x.Format(L"_mousepoint x[%d-%d=%2d] y[%d-%d=%2d]",
				_mousepoint.x, lastPoint.x, _mousepoint.x - lastPoint.x,
				_mousepoint.y, lastPoint.y, _mousepoint.y - lastPoint.y);
			OutputDebugString(x);
			lastPoint = _mousepoint;
		}
		//������  
		if (wParam == WM_LBUTTONDOWN || wParam == WM_RBUTTONDOWN || wParam == WM_MBUTTONDOWN || wParam == WM_LBUTTONUP || wParam == WM_RBUTTONUP || wParam == WM_MBUTTONUP) {
			//��ȡ����λ�ã������б�Ҫ���ж�


			////����Ҽ�����
			//if (Mmdlg != NULL) {
			//	if (Mmdlg->setingmenu != NULL && Mmdlg->bo_back != 1)
			//	{
			//		//�����겻�ڵ�ǰ�ͻ���λ��֮��
			//		GetCursorPos(&_mousepoint);
			//		CRect m_crect;
			//		//Mmdlg->setingmenu->GetClientRect(m_crect);
			//		Mmdlg->setingmenu->GetWindowRect(m_crect);
			//		//ScreenToClient(Mmdlg->setingmenu->m_hWnd,&m_crect);
			//		if (m_crect.bottom > _mousepoint.y && m_crect.top < _mousepoint.y &&
			//			m_crect.left<_mousepoint.x && m_crect.right >_mousepoint.x
			//			) {
			//			;  //ɶҲ����

			//		}
			//		else {
			//			delete[] Mmdlg->setingmenu;
			//			Mmdlg->setingmenu = NULL;

			//		}
			//	}
			//	Mmdlg->bo_back = 0;

			//}

		}
	}
	default:   break;
	}

	return CallNextHookEx(NULL, nCode, wParam, lParam);
}