#pragma once
#include <windows.h>
#include <stdio.h>
#include "GamUser.h"
class ProcessFind
{

public:
	static ProcessFind* getInstance() {
		static ProcessFind pf;
		return &pf;
	}
	struct Finded_Obj {
		HWND hWnd;
		DWORD pid;
		CString titlename;
		HWND gpsValueWnd;
	};

	std::vector<std::shared_ptr<GameObj>> gameUserObjs;

	void findObj()
	{
		gameUserObjs.clear();
		TCHAR windowTitle[256];

		{
			HWND hWnd = NULL;
			DWORD pid = 0;
			while (hWnd = FindWindowEx(NULL, hWnd, L"SlOnline", NULL))
			{

				GetWindowText(hWnd, windowTitle, sizeof(windowTitle));
				CString xt = windowTitle;

				GetWindowThreadProcessId(hWnd, &pid);
				gameUserObjs.emplace_back(std::make_shared<GameObj>(hWnd, pid, xt));
			}
		}
	}

};