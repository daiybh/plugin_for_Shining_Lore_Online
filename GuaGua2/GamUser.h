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
		PressAlt(false);
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
	bool goto_XY(int curX,int curY, GPSXY destGPS);
	CString goto_Center( int x1, int y1, int x4, int y4);
	
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
		FKey('5');
	}
	bool bAltDown() {

		return m_Sharemem->getData() == 1;
	}
	
	void PressAlt(bool bDown)
	{		 
		m_Sharemem->writeData(bDown?1:0);
		::SendMessage(hWnd, WM_SYSKEYDOWN, VK_MENU, 0);
		::SendMessage(hWnd, WM_KEYUP, VK_MENU, 0);		
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
	void pickup(int DestX,int DestY );
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