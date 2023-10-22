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
			showText.Format(L"curX(%d)С�� destX(%d) ����", curX, destGPS.x);
			logFunc(showText);
			this->move_left_one();
		}
		else if (curX > destGPS.x)
		{
			showText.Format(L"curX(%d)���� destX(%d) ����", curX, destGPS.x);
			logFunc(showText);
			this->move_right_one();
		}
		else if (curY < destGPS.y)
		{
			showText.Format(L"curY(%d)С�� destY(%d) ����", curY, destGPS.y);
			logFunc(showText);
			this->move_down_one();
		}
		else if (curY > destGPS.y)
		{
			showText.Format(L"curY(%d)���� destY(%d) ����", curY, destGPS.y);
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
			showText.Format(L"x(%d)С�� x1(%d) ����", currentGPSX, x1);

			//logFunc(showText);
			this->move_left_one();

			//������ ����x �ȸղ�С�ˣ�������

			int lastGPSX = currentGPSX, lastGPSY = currentGPSY;
			hsn.getGPS(currentGPSX, currentGPSY);
			if (currentGPSX < lastGPSX)
			{
				CString s;
				s.Format(L"�Ѿ������� ����x %d �ȸղ� %d С�ˣ�������",currentGPSX,lastGPSX);
				OutputDebugString(s);
				logFunc(s);
				turn_map();
			}
		}
		else if (currentGPSX > x4)
		{
			showText.Format(L"x(%d)�� x4(%d) ����", currentGPSX, x4);
			//logFunc(showText);
			this->move_right_one();			

			int lastGPSX = currentGPSX, lastGPSY = currentGPSY;
			hsn.getGPS(currentGPSX, currentGPSY);
			if (currentGPSX > lastGPSX)
			{
				CString s;
				s.Format(L"�Ѿ������� ����x %d �ȸղ� %d ���ˣ�������", currentGPSX, lastGPSX);
				OutputDebugString(s);
				logFunc(s);
				turn_map();
			}
		}
		else if (currentGPSY < y1)
		{
			showText.Format(L"y(%d)С�� y1(%d) ����", currentGPSY, y1);
			//logFunc(showText);
			this->move_down_one();



			int lastGPSX = currentGPSX, lastGPSY = currentGPSY;
			hsn.getGPS(currentGPSX, currentGPSY);
			if (currentGPSY < lastGPSY)
			{
				CString s;
				s.Format(L"�Ѿ������� ����y %d �ȸղ� %d С�ˣ�������", currentGPSY, lastGPSY);
				OutputDebugString(s);
				logFunc(s);
				turn_map();
			}
		}
		else if (currentGPSY > y4)
		{
			showText.Format(L"y(%d)���� y4(%d) ����", currentGPSY, y4);
			//logFunc(showText);
			this->move_top_one();

			int lastGPSX = currentGPSX, lastGPSY = currentGPSY;
			hsn.getGPS(currentGPSX, currentGPSY);
			if (currentGPSY > lastGPSY)
			{
				CString s;
				s.Format(L"�Ѿ������� ����y %d �ȸղ� %d ���ˣ�������", currentGPSY, lastGPSY);
				OutputDebugString(s);
				logFunc(s);
				turn_map();
			}
		}
		else
		{
			showText.Format(L"����");
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
				g_splitText=  L"���ƶ��� 3475/2715";
				return false;
			}
			//������
			this->move_one_offset = 80;
			int X = center_X;
			int Y = center_y-move_one_offset;

			this->moveMouse(X, Y);
			Sleep(1000);
			this->LeftClick(X, Y);
			Sleep(1000);
			//��ֽ�
			
			Y = center_y + 75;
			this->moveMouse(X, Y);
			Sleep(1000);
			this->LeftClick(X, Y);
			Sleep(1000);
			//
			//���һ��
			Y -= 36;
			this->moveMouse(X, Y);
			Sleep(1000);
			this->LeftClick(X, Y);
			//
			CString x;
			x.Format(L"�ɹ�\n���λ���� 3475/2715\n    ��ǰ��%d/%d��",currentGPSX,currentGPSY);
			g_splitText= x;
			return true;
		}
	}
	bool  checkIfoutGPS()
	{
		if (settingGPSX == 0 && settingGPSY == 0)
		{
			g_GoCenterInfo = L"���ĵ㻹û����";
			return false;
		}
		if (currentGPSX == 0 && currentGPSY == 0)
		{
			g_GoCenterInfo = L"��ǰ����δ��ȡ��";
			return false;
		}
		if (currentGPSX == settingGPSX && currentGPSY == settingGPSY)
		{
			bNeedGoCenter = false;
			g_GoCenterInfo = L"�Ѿ������������";
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
		
		pRCilick(center_X,center_y-100);//��������
		pRCilick(center_X-100,center_y);//������
		pRCilick(center_X+100,center_y);//������
		pRCilick(center_X,center_y);//������		
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
			{// ģ������������  

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