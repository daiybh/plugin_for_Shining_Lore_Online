#pragma once
#include "ObjecInfo_HP_SP_NP.h"
#include "Config.h"

#include "ObjecInfo_HP_SP_NP.h"
#include "..\detours_cmake_tpl\hooking_dll_tpl\sharemem.h"
#include "dll_injector.h"
#include <thread>
class GameObj {

public:

	GameObj(HWND h, DWORD pid, CString name) {
		this->hWnd = h;
		this->pid = pid;
		this->titlename = name;

		GetWindowRect(h, &rect);

		center_X = (rect.right - rect.left) / 2;
		center_y = (rect.bottom - rect.top) / 2;
		hsn.open(pid);
		if (m_Sharemem)
			delete m_Sharemem;

		this->m_Sharemem = new Sharemem();
		this->m_Sharemem->CreateSharemem(this->pid);
		m_ExitEvent = new CEvent(false);

		wchar_t pszFilePath[MAX_PATH];
		memset(pszFilePath, 0, sizeof(pszFilePath) * sizeof(char));
		GetModuleFileName(NULL, pszFilePath, MAX_PATH);
		PathRemoveFileSpec(pszFilePath);		
		m_dllPath.Format(L"%s\\hooking_dll_tpl.dll", pszFilePath);
		InjectDll(true);
	}
	~GameObj()
	{
		stop();
		InjectDll(false);
	}
	uint64_t loopcount = 0;
private:
	CEvent* m_ExitEvent = nullptr;

	bool bExit = false;
	Sharemem* m_Sharemem = nullptr;
public:
	CString g_GoCenterInfo;

	ConfigItem m_ConfigItem;

	void InjectDll(bool bload) 
	{
		m_bInjected = Dll_injector::action_unload(pid, m_dllPath.GetString());
		if (bload)
		{
			m_bInjected = Dll_injector::action_load(pid, m_dllPath.GetString());
		}			
	}
	CString m_dllPath;
	bool m_bInjected = false;
	std::function<void(CString)> m_logFunc = nullptr;
	void logFunc(CString log)
	{
		if (m_logFunc != nullptr)
			m_logFunc(log);
	}
	void startWork(std::function<void(CString)> logFunc) {
		m_logFunc = logFunc;
		m_workthread =new  std::thread(&GameObj::workthread, this);
	}
	std::thread *m_workthread=nullptr;
	void stop() {
		bExit = true;
		m_ExitEvent->SetEvent();

		if (m_workthread && m_workthread->joinable())
			m_workthread->join();
		m_workthread = nullptr;
	}
	void workthread();
	void handlePickUP();
	bool bNeedGoCenter = false;
	void handleAttack();

	void isNeedTurnFace() {
		int lastGPSX=currentGPSX, lastGPSY = currentGPSY;
		hsn.getGPS(currentGPSX, currentGPSY);

	}
	struct GPSXY {
		int x;
		int y;
	};
	bool goto_XY(int curX,int curY, GPSXY destGPS)
	{
		if (curX == destGPS.x && curY== destGPS.y)
		{
			return true;
		}
		CString  showText;
		showText.Format(L"goto [%d,%d]-->[%d,%d]", curX, curY, destGPS.x, destGPS.y);
		logFunc(showText);
		if (curX < destGPS.x)
		{
			showText.Format(L"curX(%d)小于 destX(%d) 往左", curX, destGPS.x);
			logFunc(showText);
			this->move_left_one();
		}
		else if (curX > destGPS.x)
		{
			showText.Format(L"curX(%d)大于 destX(%d) 往右", curX, destGPS.x);
			logFunc(showText);
			this->move_right_one();
		}
		else if (curY < destGPS.y)
		{
			showText.Format(L"curY(%d)小于 destY(%d) 往下", curY, destGPS.y);
			logFunc(showText);
			this->move_down_one();
		}
		else if (curY > destGPS.y)
		{
			showText.Format(L"curY(%d)大于 destY(%d) 往上", curY, destGPS.y);
			logFunc(showText);
			this->move_top_one();
		}
		return false;
	}
	CString goto_Center( int x1, int y1, int x4, int y4)
	{
		CString  showText = L""; bNeedGoCenter = true;
		if (currentGPSX < x1)
		{
			showText.Format(L"x(%d)小于 x1(%d) 往左", currentGPSX, x1);

			//logFunc(showText);
			this->move_left_one();

			//向左了 但是x 比刚才小了，方向反了

			int lastGPSX = currentGPSX, lastGPSY = currentGPSY;
			hsn.getGPS(currentGPSX, currentGPSY);
			if (currentGPSX < lastGPSX)
			{
				CString s;
				s.Format(L"已经向左了 但是x %d 比刚才 %d 小了，方向反了",currentGPSX,lastGPSX);
				OutputDebugString(s);
				logFunc(s);
				turn_map();
			}
		}
		else if (currentGPSX > x4)
		{
			showText.Format(L"x(%d)于 x4(%d) 往右", currentGPSX, x4);
			//logFunc(showText);
			this->move_right_one();			

			int lastGPSX = currentGPSX, lastGPSY = currentGPSY;
			hsn.getGPS(currentGPSX, currentGPSY);
			if (currentGPSX > lastGPSX)
			{
				CString s;
				s.Format(L"已经往右了 但是x %d 比刚才 %d 大了，方向反了", currentGPSX, lastGPSX);
				OutputDebugString(s);
				logFunc(s);
				turn_map();
			}
		}
		else if (currentGPSY < y1)
		{
			showText.Format(L"y(%d)小于 y1(%d) 往下", currentGPSY, y1);
			//logFunc(showText);
			this->move_down_one();



			int lastGPSX = currentGPSX, lastGPSY = currentGPSY;
			hsn.getGPS(currentGPSX, currentGPSY);
			if (currentGPSY < lastGPSY)
			{
				CString s;
				s.Format(L"已经往下了 但是y %d 比刚才 %d 小了，方向反了", currentGPSY, lastGPSY);
				OutputDebugString(s);
				logFunc(s);
				turn_map();
			}
		}
		else if (currentGPSY > y4)
		{
			showText.Format(L"y(%d)大于 y4(%d) 往上", currentGPSY, y4);
			//logFunc(showText);
			this->move_top_one();

			int lastGPSX = currentGPSX, lastGPSY = currentGPSY;
			hsn.getGPS(currentGPSX, currentGPSY);
			if (currentGPSY > lastGPSY)
			{
				CString s;
				s.Format(L"已经往上了 但是y %d 比刚才 %d 大了，方向反了", currentGPSY, lastGPSY);
				OutputDebugString(s);
				logFunc(s);
				turn_map();
			}
		}
		else
		{
			showText.Format(L"正常");
			bNeedGoCenter = false;
		}

		return showText;
	}
	CString g_splitText = L"";
	bool gotoSplitPoint() {
		int splitPointX = 3475;
		int splitPointY = 2715;

		int winWith = (rect.right - rect.left);
		int winHeight = (rect.bottom - rect.top) ;
		winHeight = 960;
		winWith = 960*2;
		int lastCurX = 0, lastCurY = 0;
		int continueSameCount = 0;
		do
		{
			hsn.getGPS(currentGPSX, currentGPSY);

			int curX = hsn.bb1.x/1;
			int curY = hsn.bb1.y/1;

			
			int destX = splitPointX / 1;
			int destY = splitPointY / 1;
			if (curX == destX && curY == destY)
				break;
			if (lastCurX == curX && lastCurY == curY)
				continueSameCount++;
			else
			{
				lastCurX = curX;
				lastCurY = curY;
				continueSameCount = 0;
			}
			int X = center_X;
			int Y = center_y;

			if (curX != destX)
			{
				X += (curX - destX)*winWith/960;
			}
			if (curY != destY)
			{
				Y -= (curY - destY)*winHeight/960;
			}
			CString x;
			x.Format(L"\ngotoSplitPoint [%d,%d,%d,%d]  X[%d->%d] Y[%d->%d]\n",
				curX, splitPointX, curY, splitPointY,X,center_X,Y,center_y);
			OutputDebugString(x);

			if (continueSameCount > 10)
			{
				break;
			}
			this->moveMouse(X, Y);
			Sleep(1000);
			this->ALT_Down();
			this->LeftClick(X, Y);

			this->ALT_Up();
			Sleep(1000);
		} while (1);
		return 1;
	}
	bool doSplit() {
		{
			gotoSplitPoint();
			hsn.getGPS(currentGPSX, currentGPSY);
			if (((int)hsn.bb1.x)/100 != 34 || int(hsn.bb1.y/100) != 27)
			{				
				g_splitText=  L"请移动到 3475/2715";
				return false;
			}
			//点箱子
			this->move_one_offset = 80;
			int X = center_X;
			int Y = center_y-move_one_offset;

			this->moveMouse(X, Y);
			Sleep(1000);
			this->LeftClick(X, Y);
			Sleep(1000);
			//点分解
			
			Y = center_y + 75;
			this->moveMouse(X, Y);
			Sleep(1000);
			this->LeftClick(X, Y);
			Sleep(1000);
			//
			//点第一行
			Y -= 36;
			this->moveMouse(X, Y);
			Sleep(1000);
			this->LeftClick(X, Y);
			//
			CString x;
			x.Format(L"成功\n最佳位置在 3475/2715\n    当前（%d/%d）",currentGPSX,currentGPSY);
			g_splitText= x;
			return true;
		}
	}
	bool  checkIfoutGPS()
	{
		if (settingGPSX == 0 && settingGPSY == 0)
		{
			g_GoCenterInfo = L"中心点还没设置";
			return false;
		}
		if (currentGPSX == 0 && currentGPSY == 0)
		{
			g_GoCenterInfo = L"当前坐标未获取到";
			return false;
		}
		if (currentGPSX == settingGPSX && currentGPSY == settingGPSY)
		{
			bNeedGoCenter = false;
			g_GoCenterInfo = L"已经在设置坐标点";
			return bNeedGoCenter;
		}
		int offset = m_ConfigItem.areaOffset;

		if (bNeedGoCenter)
		{
			offset = 0;
		}
		g_GoCenterInfo = goto_Center( settingGPSX - offset, settingGPSY - offset, settingGPSX + offset, settingGPSY + offset);
		return bNeedGoCenter;
	}

	void setCurrentGPS_To_Setting() {
		hsn.getGPS(settingGPSX, settingGPSY);
	}
	int currentGPSX = 0;
	int currentGPSY = 0;

	int settingGPSX = 0;
	int settingGPSY = 0;
	bool bSplit = false;
	ObjecInfo_HP_SP_NP hsn;
	HWND hWnd;
	DWORD pid;
	CString titlename;
	RECT rect;
	int center_X = 0;
	int center_y = 0;
	int move_one_offset = 100;
	void Press5_forNP() {
		FKey('4');
	}
	bool bAltDown() {

		return m_Sharemem->getData() == 1;
	}
	
	void ALT_Down()
	{
		//Key_down(VK_MENU); 
		m_Sharemem->writeData(1);
		::SendMessage(hWnd, WM_SYSKEYDOWN, VK_MENU, 0);
		//::SendMessage(hWnd, WM_KEYDOWN, VK_MENU, 0);
		Sleep(1000);
	}
	void ALT_Up()
	{
		m_Sharemem->writeData(0);
		//key_up(VK_LMENU);
		::SendMessage(hWnd, WM_KEYUP, VK_MENU, 0);
		Sleep(1000);
	}
	void doPickup() {
		this->pickup(center_X -10, center_y-10);
	}
	
	
	void attack()
	{
		int X = center_X;
		int Y = center_y;
		int x = center_X;
		auto pRCilick = [&](int x, int y) {
			SendMessage(hWnd, WM_MOUSEMOVE, 0, MAKELONG(x, y));
			RightClick(x, y);
			Sleep(1);
			};
		
		pRCilick(center_X,center_y-100);//身体中心
		pRCilick(center_X-100,center_y);//身体左
		pRCilick(center_X+100,center_y);//身体右
		pRCilick(center_X,center_y);//身体下		
	}
	void attackCenter()
	{
		int X = center_X;
		int Y = center_y;
		RightClick(X, Y);
	}

	bool bleftClick = true;
	
	void move_left_one()
	{
		int X = center_X - move_one_offset;
		int Y = center_y;
		g_GoCenterInfo.Format(L"move_left_one %d/%d", X, Y);
		//logFunc(g_GoCenterInfo);
		pickup(X, Y);
	}
	

	void move_right_one()
	{
		int X = center_X + move_one_offset;
		int Y = center_y;
		g_GoCenterInfo.Format(L"move_right_one %d/%d", X, Y);
		//logFunc(g_GoCenterInfo);
		pickup(X, Y);
	}


	void move_top_one(int sleep=0,bool bjustClick=false)
	{
		int X = center_X;
		int Y = center_y - move_one_offset*2 ;
		g_GoCenterInfo.Format(L"move_top_one %d/%d", X, Y);
		//logFunc(g_GoCenterInfo);
		if (bjustClick)
			move(X, Y,sleep);
		else
			pickup(X, Y);
	}


	void move_down_one(int sleep = 0, bool bjustClick=false)
	{
		
		int X = center_X;
		int Y = center_y + move_one_offset/2;
		g_GoCenterInfo.Format(L"move_top_one %d/%d", X, Y);
		//logFunc(g_GoCenterInfo);
		if (bjustClick)
			move(X, Y, sleep);
		else
			pickup(X, Y);
	}
	bool isBreakOp()
	{
		if (hsn.info.HP == hsn.info.HPMax)return true;
		return bExit;
	}
	void gobackMainFun(int func)
	{
		FKey(VK_F1 + func);
	}
	void F1() {
		logFunc(L"press F1");
		FKey(VK_F1);
	}
	void F2() {
		logFunc(L"press F2");
		FKey(VK_F2);
	}
	void F3() {
		logFunc(L"press F3");
		FKey(VK_F3);
	}
	void F4() {
		logFunc(L"press F4");
		FKey(VK_F4);
	}
	void F5() {
		logFunc(L"press F5");
		FKey(VK_F5);
	}
	void turn_map() {
		logFunc(L"press Z");
		FKey('Z');
		
	}
	void moveMouse(int x, int y)
	{
		SendMessage(hWnd, WM_MOUSEMOVE, 0, MAKELONG(x, y));
	}
	void LeftClick(int x, int y)
	{
		send_message(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 2, x, y);
	}
private:
	void pickup(int DestX,int DestY )
	{
		this->ALT_Down();
		int x1, x2, y1, y2;
		x1 = x2 = center_X;
		y1 = y2 = center_y;
		if (DestX > center_X)
		{
			x1 = center_X;
			x2 = DestX;
		}
		else if (DestX < center_X)
		{
			x2 = center_X;
			x1 = DestX;
		}
		else if (DestY < center_y)
		{
			y2 = center_y;
			y1 = DestY;
		}
		else if (DestY > center_y)
		{
			y1 = center_y;
			y2 = DestY;

		}

		for (int x = x1; x <= x2; x += 5)
		{
			for (int y = y1; y <=  y2; y += 5)
			{// 模拟鼠标左键单击  

				move(x, y);
				Sleep(10);
				if (bExit)return;
			}
		}

		Sleep(1000);
		this->ALT_Up();
	}
	void FKey(byte key) {
		Key_down(key);
		key_up(key);
	}
	void move(int x, int y, int sleep=0)
	{
		moveMouse(x, y);

		if (bleftClick)
		{
			Sleep(sleep);
			LeftClick(x, y);
		}
	}
	
	void Right_down(int x, int y)
	{
		send_message(MOUSEEVENTF_RIGHTDOWN, 1, x, y);
	}
	void Right_up(int x, int y)
	{
		send_message(MOUSEEVENTF_MIDDLEUP, 1, x, y);
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