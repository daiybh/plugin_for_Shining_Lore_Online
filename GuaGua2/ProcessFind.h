#pragma once
#include <windows.h>
#include <stdio.h>
class GameObj {

public:
	GameObj(HWND h, DWORD pid, CString name) {
		this->hWnd = h;
		this->pid = pid;
		this->titlename = name;

		GetWindowRect(h, &rect);

		center_X = (rect.right - rect.left) / 2;
		center_y = (rect.bottom - rect.top) / 2;

	}
	HWND hWnd;
	DWORD pid;
	CString titlename;
	RECT rect;
	int center_X = 0;
	int center_y = 0;
	int move_one_offset = 100;
	void ALT_Down()
	{
		//Key_down(VK_MENU); 
			::SendMessage(hWnd, WM_SYSKEYDOWN, VK_MENU, 0);
		//::SendMessage(hWnd, WM_KEYDOWN, VK_MENU, 0);
	}
	void ALT_Up()
	{
		//key_up(VK_LMENU);
		::SendMessage(hWnd, WM_KEYUP, VK_MENU, 0);
	}
	void pickup()
	{
		int X = center_X ;
		int Y = center_y ; 
		LeftClick(X, Y);
		LeftClick(X, Y);
	}
	void attackCenter()
	{
		RightClick(center_X, center_y);
		RightClick(center_X, center_y);
	}
	
	void move_left_top_one()
	{
		int X = center_X - move_one_offset;
		int Y = center_y - move_one_offset;
		move(X, Y);
	}

	void move_left_down_one()
	{
		int X = center_X - move_one_offset;
		int Y = center_y + move_one_offset;
		move(X, Y);
	}
	void move_left_one()
	{
		int X = center_X - move_one_offset;
		int Y = center_y;
		move(X, Y);
	}
	void move_right_down_one()
	{
		int X = center_X + move_one_offset;
		int Y = center_y + move_one_offset;
		move(X, Y);
	}
	void move_right_top_one()
	{
		int X = center_X + move_one_offset;
		int Y = center_y - move_one_offset;
		move(X, Y);
	}

	void move_right_one()
	{
		int X = center_X + move_one_offset;
		int Y = center_y;
		move(X, Y);
	}


	void move_top_one()
	{
		int X = center_X;
		int Y = center_y - move_one_offset * 3;
		move(X, Y);
	}


	void move_down_one()
	{
		int X = center_X;
		int Y = center_y + move_one_offset;
		move(X, Y);
	}
	
	void F1() {
		FKey(VK_F1);		
	}
	void F2() {	
		FKey(VK_F2);
	}
	void F3() {
		FKey(VK_F3);
	}
	void F4() {
		FKey(VK_F4);
	}
	void F5() {
		FKey(VK_F5);
	}
private:
	void FKey(byte key) {
		Key_down(key);
		key_up(key);
	}
	void move(int x, int y)
	{
		SendMessage(hWnd, WM_MOUSEMOVE, 0, MAKELONG(x, y));
		LeftClick(x, y);
	}
	void LeftClick(int x, int y)
	{
		send_message(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 2, x, y);
	}
	void Right_down(int x, int y)
	{
		send_message(MOUSEEVENTF_RIGHTDOWN, 1, x, y);
	}
	void Right_up(int x, int y)
	{
		send_message(MOUSEEVENTF_RIGHTUP, 1, x, y);
	}
	void RightClick(int x, int y)
	{
		send_message(MOUSEEVENTF_RIGHTUP | MOUSEEVENTF_RIGHTDOWN, 1, x, y);
	}
	void send_message(int dwFlags, int cButtons, int x, int y)
	{
		if ((dwFlags | MOUSEEVENTF_LEFTDOWN) == dwFlags)
			SendMessage(hWnd, WM_LBUTTONDOWN, cButtons, MakeDWord(x, y));
		if ((dwFlags | MOUSEEVENTF_LEFTUP) == dwFlags)
			SendMessage(hWnd, WM_LBUTTONUP, cButtons, MakeDWord(x, y));
		if ((dwFlags | MOUSEEVENTF_RIGHTDOWN) == dwFlags)
			SendMessage(hWnd, WM_RBUTTONDOWN, cButtons, MakeDWord(x, y));
		if ((dwFlags | MOUSEEVENTF_RIGHTUP) == dwFlags)
			SendMessage(hWnd, WM_RBUTTONUP, cButtons, MakeDWord(x, y));
		if ((dwFlags | MOUSEEVENTF_MIDDLEDOWN) == dwFlags)
			SendMessage(hWnd, WM_MBUTTONDOWN, cButtons, MakeDWord(x, y));
		if ((dwFlags | MOUSEEVENTF_MIDDLEUP) == dwFlags)
			SendMessage(hWnd, WM_MBUTTONUP, cButtons, MakeDWord(x, y));
	}

	int MakeDWord(int low, int high)
	{
		return  MAKELONG(low, high);
	}
	void Key_down(BYTE  key)
	{
		return VK_SendKeyDownMsg(key);
		int lParam = 1;
		lParam += MapVirtualKey(key, 0) << 16;
		//2883585
		SendMessage(hWnd, WM_KEYDOWN, key, lParam);//Thread.Sleep(100);

	}
	void VK_SendKeyDownMsg(BYTE key) {
		DWORD dwVKFkeyData;
		WORD dwScanCode = MapVirtualKey(key, 0);
		dwVKFkeyData = 1;
		dwVKFkeyData |= dwScanCode << 16;
		dwVKFkeyData |= 0 << 24;
		dwVKFkeyData |= 0 << 29;
		::SendMessage(hWnd, WM_KEYDOWN, key, dwVKFkeyData);
	}
	void key_up(BYTE  key)
	{
		return VK_SendKeyUpMsg(key);
		int lParam = 1;
		lParam += MapVirtualKey(key, 0) << 16;
		//2883585
		//SendMessage(hWnd, WM_KEYDOWN, key.GetHashCode(), lParam);//Thread.Sleep(100);
		lParam += 1 << 30;
		lParam += 1 << 31;
		SendMessage(hWnd, WM_KEYUP, key, lParam);//up
	}
	void		 VK_SendKeyUpMsg(BYTE key) {
		DWORD dwVKFkeyData;
		WORD dwScanCode = MapVirtualKey(key, 0);
		dwVKFkeyData = 1;
		dwVKFkeyData |= dwScanCode << 16;
		dwVKFkeyData |= 0 << 24;
		dwVKFkeyData |= 0 << 29;

		dwVKFkeyData |= 3 << 30;
		::SendMessage(hWnd, WM_KEYUP, key, dwVKFkeyData);

	}
};
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

	std::vector<GameObj> gameUserObjs;
	
	void findObj()
	{
		gameUserObjs.clear();
		TCHAR windowTitle[256];
		
		{
			HWND hWnd = NULL;
			DWORD pid = 0;
			while (hWnd = FindWindowEx(NULL,hWnd,  L"SlOnline", NULL))
			{

				GetWindowText(hWnd, windowTitle, sizeof(windowTitle));
				CString xt = windowTitle;

				GetWindowThreadProcessId(hWnd, &pid);
				gameUserObjs.emplace_back(GameObj(hWnd, pid, xt));
			}
		}
	}

};