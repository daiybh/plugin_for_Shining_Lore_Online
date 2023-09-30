﻿
// GuaGua2Dlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "GuaGua2.h"
#include "GuaGua2Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CGuaGua2Dlg 对话框



CGuaGua2Dlg::CGuaGua2Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GUAGUA2_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGuaGua2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_GAMEUSER, m_gameUser);
	DDX_Control(pDX, IDC_COMBO_GPS, m_ComboGps);
	DDX_Control(pDX, IDC_SLIDER_POSOFFSET, m_posOffset);
	DDX_Control(pDX, IDC_SLIDER_POSOFFSET2, m_posOffset2);
}

BEGIN_MESSAGE_MAP(CGuaGua2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_SETCENTERPOS, &CGuaGua2Dlg::OnBnClickedButtonSetcenterpos)
	ON_NOTIFY(TRBN_THUMBPOSCHANGING, IDC_SLIDER_POSOFFSET, &CGuaGua2Dlg::OnTRBNThumbPosChangingSliderPosoffset)
	ON_BN_CLICKED(IDC_CHECK_NP, &CGuaGua2Dlg::OnBnClickedCheckNp)
	ON_BN_CLICKED(IDC_CHECK_PICKUP, &CGuaGua2Dlg::OnBnClickedCheckPickup)
	ON_BN_CLICKED(IDC_CHECK_ATTACK, &CGuaGua2Dlg::OnBnClickedCheckAttack)
	ON_BN_CLICKED(IDOK, &CGuaGua2Dlg::OnBnClickedOk)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_TOP, &CGuaGua2Dlg::OnBnClickedButtonTop)
	ON_BN_CLICKED(IDC_BUTTON_TOP_LEFT, &CGuaGua2Dlg::OnBnClickedButtonTopLeft)
	ON_BN_CLICKED(IDC_BUTTON_TOP_RIGHT, &CGuaGua2Dlg::OnBnClickedButtonTopRight)
	ON_BN_CLICKED(IDC_BUTTON_LEFT, &CGuaGua2Dlg::OnBnClickedButtonLeft)
	ON_BN_CLICKED(IDC_BUTTON_RIGHT, &CGuaGua2Dlg::OnBnClickedButtonRight)
	ON_BN_CLICKED(IDC_BUTTON_DOWN_LEFT, &CGuaGua2Dlg::OnBnClickedButtonDownLeft)
	ON_BN_CLICKED(IDC_BUTTON_DOWN, &CGuaGua2Dlg::OnBnClickedButtonDown)
	ON_BN_CLICKED(IDC_BUTTON_DOWN_RIGHT, &CGuaGua2Dlg::OnBnClickedButtonDownRight)
	ON_BN_CLICKED(IDC_BUTTON_ATTACK, &CGuaGua2Dlg::OnBnClickedButtonAttack)
	ON_CBN_SELCHANGE(IDC_COMBO_GAMEUSER, &CGuaGua2Dlg::OnCbnSelchangeComboGameuser)
	ON_BN_CLICKED(IDCANCEL, &CGuaGua2Dlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CGuaGua2Dlg 消息处理程序
#include "Config.h"
#include "ProcessFind.h"

enum timerEvent {
	timer_updateGPS = 200,
	timer_NP = 201,
	timer_PICKUP,
	timer_F1,
	timer_F2,
	timer_F3,
	timer_F4,
	timer_F5
};
BOOL CGuaGua2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	Config::getInstance();
	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	CString info = _T("1. 先选角色 \n \
		2. 选GPS  如果下面显示的坐标是当前的就是正确的\n  \
		3. 在游戏中跑到想在的位置 \n \
		4.  点”选中GPS 后点这里设置中心“\n ");

	SetDlgItemText(IDC_EDIT_INFO, info);

	ProcessFind::getInstance()->findObj();

	for (int i = 0; i < ProcessFind::getInstance()->gameUserObjs.size(); i++)
	{
		auto gameUser = ProcessFind::getInstance()->gameUserObjs[i];
		int ips = m_gameUser.AddString(gameUser.titlename);
		m_gameUser.SetItemData(ips, i);
	}
	for (int i = 0; i < ProcessFind::getInstance()->gpsObjs.size(); i++)
	{
		auto gps = ProcessFind::getInstance()->gpsObjs[i];
		CString title;
		title.Format(_T("%d %s"), gps.pid, gps.titlename);
		int ips = m_ComboGps.AddString(title);
		m_ComboGps.SetItemData(ips, i);
	}
	m_posOffset.SetRange(0, 100);
	m_posOffset.SetPos(40);
	m_posOffset2.SetRange(0, 1000);
	m_posOffset2.SetPos(40);


	SetTimer(timer_updateGPS, 1000, NULL);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CGuaGua2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CGuaGua2Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CGuaGua2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


int cur_centerX = 0;
int cur_centerY = 0;
void CGuaGua2Dlg::OnBnClickedButtonSetcenterpos()
{
	CString rx;
	GetDlgItemText(IDC_STATIC_CurrentPOS, rx);

	SetDlgItemText(IDC_STATIC_centerPOS, rx);
}


void CGuaGua2Dlg::OnTRBNThumbPosChangingSliderPosoffset(NMHDR* pNMHDR, LRESULT* pResult)
{
	// 此功能要求 Windows Vista 或更高版本。
	// _WIN32_WINNT 符号必须 >= 0x0600。
	NMTRBTHUMBPOSCHANGING* pNMTPC = reinterpret_cast<NMTRBTHUMBPOSCHANGING*>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


void CGuaGua2Dlg::OnBnClickedCheckNp()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CGuaGua2Dlg::OnBnClickedCheckPickup()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CGuaGua2Dlg::OnBnClickedCheckAttack()
{
	// TODO: 在此添加控件通知处理程序代码
}

static std::string ConvertCStringToUTF8(CString strValue)
{
	std::wstring wbuffer;
#ifdef _UNICODE
	wbuffer.assign(strValue.GetString(), strValue.GetLength());
#else
	/*
	 * 转换ANSI到UNICODE
	 * 获取转换后长度
	 */
	int length = ::MultiByteToWideChar(CP_ACP, MB_ERR_INVALID_CHARS, (LPCTSTR)strValue, -1, NULL, 0);
	wbuffer.resize(length);
	/* 转换 */
	MultiByteToWideChar(CP_ACP, 0, (LPCTSTR)strValue, -1, (LPWSTR)(wbuffer.data()), wbuffer.length());
#endif

	/* 获取转换后长度 */
	int length = WideCharToMultiByte(CP_UTF8, 0, wbuffer.data(), wbuffer.size(), NULL, 0, NULL, NULL);
	/* 获取转换后内容 */
	std::string buffer;
	buffer.resize(length);

	WideCharToMultiByte(CP_UTF8, 0, strValue, -1, (LPSTR)(buffer.data()), length, NULL, NULL);
	return(buffer);
}


static CString ConvertUTF8ToCString(std::string utf8str)
{
	/* 预转换，得到所需空间的大小 */
	int nLen = ::MultiByteToWideChar(CP_UTF8, NULL,
		utf8str.data(), utf8str.size(), NULL, 0);
	/* 转换为Unicode */
	std::wstring wbuffer;
	wbuffer.resize(nLen);
	::MultiByteToWideChar(CP_UTF8, NULL, utf8str.data(), utf8str.size(),
		(LPWSTR)(wbuffer.data()), wbuffer.length());

#ifdef UNICODE
	return(CString(wbuffer.data(), wbuffer.length()));
#else
	/*
	 * 转换为ANSI
	 * 得到转换后长度
	 */
	nLen = WideCharToMultiByte(CP_ACP, 0,
		wbuffer.data(), wbuffer.length(), NULL, 0, NULL, NULL);

	std::string ansistr;
	ansistr.resize(nLen);

	/* 把unicode转成ansi */
	WideCharToMultiByte(CP_ACP, 0, (LPWSTR)(wbuffer.data()), wbuffer.length(),
		(LPSTR)(ansistr.data()), ansistr.size(), NULL, NULL);
	return(CString(ansistr.data(), ansistr.length()));
#endif
}
ConfigItem g_item;
void CGuaGua2Dlg::OnCbnSelchangeComboGameuser()
{
	{
		m_gameUser.GetCurSel();
		CString curUserName;
		m_gameUser.GetWindowText(curUserName);
		if (curUserName == "")return;
		ConfigItem item;
		std::string sz2 = CT2A(curUserName.GetBuffer()); //转化为非unicode.
		item.name = sz2;

		Config c;
		c.load(item);

		SetDlgItemInt(IDC_EDIT_TIME_PICKUP, item.pickupTime);
		SetDlgItemInt(IDC_EDIT_TIME_F1, item.f1Time);
		SetDlgItemInt(IDC_EDIT_TIME_F2, item.f2Time);
		SetDlgItemInt(IDC_EDIT_TIME_F3, item.f3Time);
		SetDlgItemInt(IDC_EDIT_TIME_F4, item.f4Time);
		SetDlgItemInt(IDC_EDIT_TIME_F5, item.f5Time);

		m_posOffset.SetPos(item.areaOffset);
		CheckDlgButton(IDC_CHECK_NP, item.NP);
		CheckDlgButton(IDC_CHECK_ATTACK, item.attack);
		CheckDlgButton(IDC_CHECK_PICKUP, item.pickup);
		g_item = item;
	}
}
#include <thread>
std::thread g_thread;
bool bExit = false;
uint64_t loopcount = 0;
void CGuaGua2Dlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码	
	m_gameUser.GetCurSel();
	CString curUserName;
	m_gameUser.GetWindowText(curUserName);
	if (curUserName == "")return;

	ConfigItem item;
	std::string sz2 = CT2A(curUserName.GetBuffer()); //转化为非unicode.
	item.name = sz2;
	item.areaOffset = m_posOffset.GetPos();
	item.NP = IsDlgButtonChecked(IDC_CHECK_NP);
	item.pickup = IsDlgButtonChecked(IDC_CHECK_PICKUP);
	item.attack = IsDlgButtonChecked(IDC_CHECK_ATTACK);
	item.pickupTime = GetDlgItemInt(IDC_EDIT_TIME_PICKUP);
	item.f1Time = GetDlgItemInt(IDC_EDIT_TIME_F1);
	item.f2Time = GetDlgItemInt(IDC_EDIT_TIME_F2);
	item.f3Time = GetDlgItemInt(IDC_EDIT_TIME_F3);
	item.f4Time = GetDlgItemInt(IDC_EDIT_TIME_F4);
	item.f5Time = GetDlgItemInt(IDC_EDIT_TIME_F5);

	item.stepOffset = m_posOffset2.GetPos();
	Config c;
	c.save(item);

	g_item = item;

	g_thread = std::thread([&]()
		{
			loopcount = 0;
			bExit = false;
			bool bSetRange = false;
			while (!bExit)
			{
				Sleep(1000);
				int user = m_gameUser.GetCurSel();
				if (user != -1)
				{
					GameObj& gameUser = ProcessFind::getInstance()->gameUserObjs[user];
					if (!bSetRange)
					{
						m_posOffset2.SetRange(0, (gameUser.rect.bottom - gameUser.rect.top) / 2);
						bSetRange = true;
					}
					item.stepOffset = m_posOffset2.GetPos();

					gameUser.move_one_offset = item.stepOffset;

					gameUser.ALT_Down();
					uint64_t dNow = GetTickCount();
					if (item.pickup)
					{
						if (dNow - g_item.last_PickupTime > g_item.pickupTime * 1000)
						{
							g_item.cout_pickup++; gameUser.pickup(); g_item.last_PickupTime = dNow;
						}
					}
					if (item.attack)
					{
						if (dNow - g_item.last_f1Time > g_item.f1Time * 1000)
						{
							g_item.cout_f1++; gameUser.F1(); g_item.last_f1Time = dNow; gameUser.attackCenter();
						}
						if (dNow - g_item.last_f2Time > g_item.f2Time * 1000)
						{
							g_item.cout_f2++; gameUser.F2(); g_item.last_f2Time = dNow; gameUser.F1(); gameUser.attackCenter();
						}
						if (dNow - g_item.last_f3Time > g_item.f3Time * 1000)
						{
							g_item.cout_f3++; gameUser.F3(); g_item.last_f3Time = dNow; gameUser.F1(); gameUser.attackCenter();
						}
						if (dNow - g_item.last_f4Time > g_item.f4Time * 1000)
						{
							g_item.cout_f4++; gameUser.F4(); g_item.last_f4Time = dNow; gameUser.F1(); gameUser.attackCenter();
						}
						if (dNow - g_item.last_f5Time > g_item.f5Time * 1000)
						{
							g_item.cout_f5++; gameUser.F5(); g_item.last_f5Time = dNow; gameUser.F1(); gameUser.attackCenter();
						}
					}
					switch (loopcount % 4)
					{
					case 0:	gameUser.move_top_one(); break;
					case 1: gameUser.move_right_one(); break;
					case 2: gameUser.move_down_one(); break;
					case 3: gameUser.move_left_one(); break;
					}

					//gameUser.ALT_Up();
				}

				loopcount++;
			}
			loopcount = 9999999999999999999;
		});
}

void CGuaGua2Dlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	bExit = true;
	if (g_thread.joinable())
		g_thread.join();
}

void CGuaGua2Dlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == timer_updateGPS)
	{
		int user = m_gameUser.GetCurSel();
		int gps = m_ComboGps.GetCurSel();
		CString ss;
		if (gps != -1)
		{
			SetDlgItemText(IDC_STATIC_CurrentPOS, ProcessFind::getInstance()->getGPSValue(gps));
		}
		ss.Format(_T("%d>>user:%d gps:%d"), loopcount, user, gps);
		SetWindowText(ss);

		SetDlgItemInt(IDC_STATIC_PICKUP, g_item.cout_pickup);
		SetDlgItemInt(IDC_STATIC_F1, g_item.cout_f1);
		SetDlgItemInt(IDC_STATIC_F2, g_item.cout_f2);
		SetDlgItemInt(IDC_STATIC_F3, g_item.cout_f3);
		SetDlgItemInt(IDC_STATIC_F4, g_item.cout_f4);
		SetDlgItemInt(IDC_STATIC_F5, g_item.cout_f5);
	}

	CDialogEx::OnTimer(nIDEvent);
}


void CGuaGua2Dlg::OnBnClickedButtonTop()
{
	int user = m_gameUser.GetCurSel();
	if (user == -1)return;


	ProcessFind::getInstance()->gameUserObjs[user].move_top_one();

}


void CGuaGua2Dlg::OnBnClickedButtonTopLeft()
{
	int user = m_gameUser.GetCurSel();
	if (user == -1)return;


	ProcessFind::getInstance()->gameUserObjs[user].move_left_top_one();
}


void CGuaGua2Dlg::OnBnClickedButtonTopRight()
{
	int user = m_gameUser.GetCurSel();
	if (user == -1)return;


	ProcessFind::getInstance()->gameUserObjs[user].move_right_top_one();
}


void CGuaGua2Dlg::OnBnClickedButtonLeft()
{
	int user = m_gameUser.GetCurSel();
	if (user == -1)return;


	ProcessFind::getInstance()->gameUserObjs[user].move_left_one();
}


void CGuaGua2Dlg::OnBnClickedButtonRight()
{
	int user = m_gameUser.GetCurSel();
	if (user == -1)return;


	ProcessFind::getInstance()->gameUserObjs[user].move_right_one();
}


void CGuaGua2Dlg::OnBnClickedButtonDownLeft()
{
	int user = m_gameUser.GetCurSel();
	if (user == -1)return;


	ProcessFind::getInstance()->gameUserObjs[user].move_left_down_one();
}


void CGuaGua2Dlg::OnBnClickedButtonDown()
{
	int user = m_gameUser.GetCurSel();
	if (user == -1)return;


	ProcessFind::getInstance()->gameUserObjs[user].move_down_one();
}


void CGuaGua2Dlg::OnBnClickedButtonDownRight()
{
	int user = m_gameUser.GetCurSel();
	if (user == -1)return;


	ProcessFind::getInstance()->gameUserObjs[user].move_right_down_one();
}


void CGuaGua2Dlg::OnBnClickedButtonAttack()
{
	int user = m_gameUser.GetCurSel();
	if (user == -1)return;


	ProcessFind::getInstance()->gameUserObjs[user].attackCenter();
}

