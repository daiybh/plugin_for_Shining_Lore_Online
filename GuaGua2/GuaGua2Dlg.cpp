
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

#include "Config.h"
#include "ProcessFind.h"

#include "ObjecInfo_HP_SP_NP.h"
#include "..\detours_cmake_tpl\hooking_dll_tpl\sharemem.h"

Sharemem* g_Sharemem = nullptr;
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

CString g_GoCenterInfo;
#include <thread>
CEvent g_event(false);
bool bExit = false;
uint64_t loopcount = 0;

int currentGPSX = 0;
int currentGPSY = 0;

int settingGPSX = 0;
int settingGPSY = 0;

ConfigItem g_item;

ObjecInfo_HP_SP_NP hsn;
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
	, m_mainFuncType(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGuaGua2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_GAMEUSER, m_gameUser);
	DDX_Control(pDX, IDC_SLIDER_POSOFFSET, m_posOffset);
	DDX_Control(pDX, IDC_SLIDER_POSOFFSET2, m_posOffset2);
	DDX_Radio(pDX, IDC_RADIO_F1, m_mainFuncType);
	DDX_Control(pDX, IDC_RADIO_F1, m_radio_FUN);
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
	ON_BN_CLICKED(IDC_BUTTON_REFRESH, &CGuaGua2Dlg::OnBnClickedButtonRefresh)
	ON_BN_CLICKED(IDC_BUTTON_START, &CGuaGua2Dlg::OnBnClickedButtonStart)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_POSOFFSET, &CGuaGua2Dlg::OnNMReleasedcaptureSliderPosoffset)
	ON_BN_CLICKED(ID_BUTTON_READMEM, &CGuaGua2Dlg::OnBnClickedButtonReadmem)
	ON_BN_CLICKED(IDC_BUTTON_PICKUP, &CGuaGua2Dlg::OnBnClickedButtonPickup)
	ON_BN_CLICKED(IDC_BUTTON_SHOWWINDOW, &CGuaGua2Dlg::OnBnClickedButtonShowwindow)
	ON_BN_CLICKED(IDC_RADIO_F1, &CGuaGua2Dlg::OnBnClickedRadioF1)
	ON_BN_CLICKED(IDC_RADIO_F2, &CGuaGua2Dlg::OnBnClickedRadioF1)
	ON_BN_CLICKED(IDC_RADIO_F3, &CGuaGua2Dlg::OnBnClickedRadioF1)
	ON_BN_CLICKED(IDC_RADIO_F4, &CGuaGua2Dlg::OnBnClickedRadioF1)
	ON_BN_CLICKED(IDC_RADIO_F5, &CGuaGua2Dlg::OnBnClickedRadioF1)
	ON_BN_CLICKED(IDC_BUTTON_INJECTION, &CGuaGua2Dlg::OnBnClickedButtonInjection)
	ON_BN_CLICKED(IDC_BUTTON_NP, &CGuaGua2Dlg::OnBnClickedButtonNp)
END_MESSAGE_MAP()


// CGuaGua2Dlg 消息处理程序

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

	CString info = _T("1. 先选角色 \r\n2. 在游戏中跑到想在的位置 \r\n3.点“选中GPS 后点这里设置中心”\r\n ");

	SetDlgItemText(IDC_EDIT_INFO, info);
	OnBnClickedButtonRefresh();
	m_posOffset.SetRange(0, 20);
	m_posOffset.SetPos(5);
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


void CGuaGua2Dlg::OnBnClickedButtonSetcenterpos()
{
	CString gpsText;

	hsn.getGPS(settingGPSX, settingGPSY);

	gpsText.Format(L"%d,%d", settingGPSX, settingGPSY);
	SetDlgItemText(IDC_STATIC_centerPOS, gpsText);

	gpsText.Format(L"%d,%d", settingGPSX - g_item.areaOffset, settingGPSY - g_item.areaOffset);
	SetDlgItemText(IDC_STATIC_X1Y1, gpsText);

	gpsText.Format(L"%d,%d", settingGPSX + g_item.areaOffset, settingGPSY - g_item.areaOffset);
	SetDlgItemText(IDC_STATIC_X2Y2, gpsText);

	gpsText.Format(L"%d,%d", settingGPSX + g_item.areaOffset, settingGPSY + g_item.areaOffset);
	SetDlgItemText(IDC_STATIC_X3Y3, gpsText);

	gpsText.Format(L"%d,%d", settingGPSX - g_item.areaOffset, settingGPSY + g_item.areaOffset);
	SetDlgItemText(IDC_STATIC_X4Y4, gpsText);
}


void CGuaGua2Dlg::OnNMReleasedcaptureSliderPosoffset(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	g_item.areaOffset = m_posOffset.GetPos();

	CString gpsText;
	gpsText.Format(L"%d,%d", settingGPSX - g_item.areaOffset, settingGPSY - g_item.areaOffset);
	SetDlgItemText(IDC_STATIC_X1Y1, gpsText);

	gpsText.Format(L"%d,%d", settingGPSX + g_item.areaOffset, settingGPSY - g_item.areaOffset);
	SetDlgItemText(IDC_STATIC_X2Y2, gpsText);

	gpsText.Format(L"%d,%d", settingGPSX + g_item.areaOffset, settingGPSY + g_item.areaOffset);
	SetDlgItemText(IDC_STATIC_X3Y3, gpsText);

	gpsText.Format(L"%d,%d", settingGPSX - g_item.areaOffset, settingGPSY + g_item.areaOffset);
	SetDlgItemText(IDC_STATIC_X4Y4, gpsText);


	SetDlgItemInt(IDC_STATIC_XY_OFFSET, g_item.areaOffset);
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
}


void CGuaGua2Dlg::OnBnClickedCheckAttack()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CGuaGua2Dlg::OnCbnSelchangeComboGameuser()
{
	{
		int user = m_gameUser.GetCurSel();
		if (user == -1)return;
		CString curUserName;
		m_gameUser.GetWindowText(curUserName);
		if (curUserName == "")return;
		ConfigItem item;
		item.name = curUserName;

		Config c;
		c.load(item);

		SetDlgItemInt(IDC_EDIT_TIME_PICKUP, item.pickupTime);
		SetDlgItemInt(IDC_EDIT_TIME_F1, item.f1Time);
		SetDlgItemInt(IDC_EDIT_TIME_F2, item.f2Time);
		SetDlgItemInt(IDC_EDIT_TIME_F3, item.f3Time);
		SetDlgItemInt(IDC_EDIT_TIME_F4, item.f4Time);
		SetDlgItemInt(IDC_EDIT_TIME_F5, item.f5Time);
		m_mainFuncType = item.mainFunc;

		m_posOffset.SetPos(item.areaOffset);
		m_posOffset2.SetPos(item.stepOffset);
		CheckDlgButton(IDC_CHECK_NP, item.NP);
		CheckDlgButton(IDC_CHECK_ATTACK, item.attack);
		CheckDlgButton(IDC_CHECK_PICKUP, item.pickup);
		g_item = item;


		int pid = ProcessFind::getInstance()->gameUserObjs[user].pid;

		hsn.open(pid);
		UpdateData(false);
		UpdateData(true);

	}
}
void CGuaGua2Dlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码	
	UpdateData(true);
	m_gameUser.GetCurSel();
	CString curUserName;
	m_gameUser.GetWindowText(curUserName);
	if (curUserName == "")return;

	ConfigItem item;
	item.name = curUserName;
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
	item.mainFunc = m_mainFuncType;

	item.stepOffset = m_posOffset2.GetPos();
	Config c;
	c.save(item);

	g_item = item;

}
bool bNeedGoCenter = false;

CString goto_Center(GameObj& curGameUser, int x1, int y1, int x4, int y4)
{
	CString  showText = L""; bNeedGoCenter = true;
	if (currentGPSX < x1)
	{
		showText.Format(L"x(%d)小于 x1(%d) 往左", currentGPSX, x1);
		curGameUser.move_left_one();
	}
	else if (currentGPSX > x4)
	{
		showText.Format(L"x(%d)于 x4(%d) 往右", currentGPSX, x4);
		curGameUser.move_right_one();
	}
	else if (currentGPSY < y1)
	{
		showText.Format(L"y(%d)小于 y1(%d) 往下", currentGPSY, y1);
		curGameUser.move_down_one();
	}
	else if (currentGPSY > y4)
	{
		showText.Format(L"y(%d)大于 y4(%d) 往上", currentGPSY, y4);
		curGameUser.move_top_one();
	}
	else
	{
		showText.Format(L"正常");
		bNeedGoCenter = false;
	}

	return showText;
}
bool  checkIfoutGPS(GameObj& curGameUser)
{
	if (settingGPSX == 0 && settingGPSY == 0)
	{
		g_GoCenterInfo= L"中心点还没设置";
		return false;
	}
	if (currentGPSX == 0 && currentGPSX == 0)
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
	int offset = g_item.areaOffset;

	if (bNeedGoCenter)
	{
		offset = 0;
	}
	g_GoCenterInfo = goto_Center(curGameUser, settingGPSX - offset, settingGPSY - offset, settingGPSX + offset, settingGPSY + offset);
	return bNeedGoCenter;
}

void CGuaGua2Dlg::OnBnClickedButtonStart()
{
	CString rtext;
	GetDlgItemText(IDC_BUTTON_START, rtext);
	if (rtext == L"开始") {
		rtext = L"停止";
		
		int user = m_gameUser.GetCurSel();
		if (user == -1)return;


		auto gameUser = ProcessFind::getInstance()->gameUserObjs[user];
		{
			m_posOffset2.SetRange(0, (gameUser.rect.bottom - gameUser.rect.top) / 2);
		}
		bExit = false;
		g_event.ResetEvent();
		m_workthread = std::thread(&CGuaGua2Dlg::workthread, this);
	}
	else {
		rtext = L"开始";
		bExit = true;
		g_event.SetEvent();

		if (m_workthread.joinable())
			m_workthread.join();
	}
	SetDlgItemText(IDC_BUTTON_START, rtext);
}


void CGuaGua2Dlg::OnBnClickedCancel()
{
	bExit = true;
	g_event.SetEvent();
	if (m_workthread.joinable())
		m_workthread.join();
	OnCancel();
}

void CGuaGua2Dlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == timer_updateGPS)
	{
		int user = m_gameUser.GetCurSel();
		loadNP();

		SetDlgItemInt(IDC_STATIC_PICKUP, g_item.cout_pickup);
		SetDlgItemInt(IDC_STATIC_F1, g_item.cout_f1);
		SetDlgItemInt(IDC_STATIC_F2, g_item.cout_f2);
		SetDlgItemInt(IDC_STATIC_F3, g_item.cout_f3);
		SetDlgItemInt(IDC_STATIC_F4, g_item.cout_f4);
		SetDlgItemInt(IDC_STATIC_F5, g_item.cout_f5);

		SetDlgItemText(IDC_STATIC_GOCENTERINFO, g_GoCenterInfo);
		
		g_item.stepOffset = m_posOffset2.GetPos();

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


void CGuaGua2Dlg::OnBnClickedButtonPickup()
{
	int user = m_gameUser.GetCurSel();
	if (user == -1)return;


	ProcessFind::getInstance()->gameUserObjs[user].ALT_Down();
}


void CGuaGua2Dlg::OnBnClickedButtonAttack()
{
	int user = m_gameUser.GetCurSel();
	if (user == -1)return;


	ProcessFind::getInstance()->gameUserObjs[user].attackCenter();
}




void CGuaGua2Dlg::OnBnClickedButtonRefresh()
{
	// TODO: 在此添加控件通知处理程序代码

	m_gameUser.ResetContent();
	ProcessFind::getInstance()->findObj();

	for (int i = 0; i < ProcessFind::getInstance()->gameUserObjs.size(); i++)
	{
		auto gameUser = ProcessFind::getInstance()->gameUserObjs[i];
		int ips = m_gameUser.AddString(gameUser.titlename);
		m_gameUser.SetItemData(ips, i);
	}

}


void CGuaGua2Dlg::OnBnClickedButtonReadmem()
{
	static int g_a = 0;
	g_Sharemem->writeData(g_a++%2);
}
void CGuaGua2Dlg::loadNP()
{
	{
		hsn.getGPS(currentGPSX, currentGPSY);
		CString gpsText;
		gpsText.Format(L"%d/%d", currentGPSX, currentGPSY);


		SetDlgItemText(IDC_STATIC_CurrentPOS, gpsText);
		CString ss;

		CString curUserName;
		m_gameUser.GetWindowText(curUserName);

		UpdateData(true);
		ss.Format(_T("%I64d>>user:%s gps:%d,%d %d %d"),
			loopcount, curUserName, currentGPSX, currentGPSY, m_mainFuncType, m_radio_FUN.GetCheck());
		SetWindowText(ss);
	}

	hsn.doRead();
	CString s;
	s.Format(L"NP:%d/%d", hsn.info.np, hsn.info.npMax);
	SetDlgItemText(IDC_STATIC_NP, s);

	s.Format(L"HP:%d/%d", hsn.info.HP, hsn.info.HPMax);
	SetDlgItemText(IDC_STATIC_HP, s);


	s.Format(L"SP:%d/%d", hsn.info.sp, hsn.info.spMax);
	SetDlgItemText(IDC_STATIC_SP, s);



}


void CGuaGua2Dlg::OnBnClickedButtonShowwindow()
{
	int user = m_gameUser.GetCurSel();
	if (user == -1)
	{
		return;
	}

	HWND hwnd = ProcessFind::getInstance()->gameUserObjs[user].hWnd;
	CString rT;
	GetDlgItemText(IDC_BUTTON_SHOWWINDOW, rT);

	if (rT == L"显示")
	{
		rT = L"隐藏";
		::ShowWindow(hwnd, 1);

		RECT rect;
		::GetWindowRect(m_hWnd, &rect);
		int screenWidth = GetSystemMetrics(SM_CXSCREEN);
		int screenHeight = GetSystemMetrics(SM_CYSCREEN);
		int windowWidth = rect.right - rect.left;
		int windowHeight = rect.bottom - rect.top;

		::SetWindowPos(hwnd, HWND_TOP, rect.right, rect.top,
			screenWidth - windowWidth - 1,
			rect.bottom - windowHeight, SWP_NOSIZE);
	}
	else
	{
		rT = L"显示";
		::ShowWindow(hwnd, 0);
	}

	SetDlgItemText(IDC_BUTTON_SHOWWINDOW, rT);
}
void handleAttack(GameObj& gameUser) {
	int iAttack = 1000; 

	if (hsn.info.HP == hsn.info.HPMax)
	{
		g_GoCenterInfo.Format(L"HP 满了 不攻击");
		return;
	}
	for (int i = iAttack; i>0  && !bExit && g_item.attack; i--)
	{
		uint64_t dNow = GetTickCount();
		if (g_item.f1Time > 0 && (dNow - g_item.last_f1Time > g_item.f1Time * 1000))
		{
			g_item.cout_f1++; gameUser.F1(); g_item.last_f1Time = dNow;
		}
		if (g_item.f2Time > 0 && (dNow - g_item.last_f2Time > g_item.f2Time * 1000))
		{
			g_item.cout_f2++; gameUser.F2(); g_item.last_f2Time = dNow;
		}
		if (g_item.f3Time > 0 && (dNow - g_item.last_f3Time > g_item.f3Time * 1000))
		{
			g_item.cout_f3++; gameUser.F3(); g_item.last_f3Time = dNow;
		}
		if (g_item.f4Time > 0 && (dNow - g_item.last_f4Time > g_item.f4Time * 1000))
		{
			g_item.cout_f4++; gameUser.F4(); g_item.last_f4Time = dNow;
		}
		if (g_item.f5Time > 0 && (dNow - g_item.last_f5Time > g_item.f5Time * 1000))
		{
			g_item.cout_f5++; gameUser.F5(); g_item.last_f5Time = dNow;
		}
		gameUser.attackCenter();
		gameUser.gobackMainFun(g_item.mainFunc);
		

		g_GoCenterInfo.Format(L"持续攻击 %d次", i);
		if (i % 100 == 0)
		{
			Sleep(1);
		}
		
	}


}
void CGuaGua2Dlg::workthread()
{
	loopcount = 0;
	bExit = false;
	bool bSetRange = false;
	while (!bExit)
	{
		loopcount++;
		DWORD dt = WaitForSingleObject(g_event, 100);
		if (dt == WAIT_OBJECT_0)break;
		hsn.getGPS(currentGPSX, currentGPSY);
		hsn.doRead();

		int user = m_gameUser.GetCurSel();
		if (user == -1)continue;

		GameObj& gameUser = ProcessFind::getInstance()->gameUserObjs[user];

		if (hsn.info.np < 50)
		{
			gameUser.Press5_forNP();
		}
		handleAttack(gameUser);

		if (checkIfoutGPS(gameUser))
			continue;
		

		gameUser.move_one_offset = g_item.stepOffset;

		gameUser.ALT_Down();
		uint64_t dNow = GetTickCount();
		if (g_item.pickup)
		{
			if (g_item.pickupTime > 0 && (dNow - g_item.last_PickupTime > g_item.pickupTime * 1000))
			{
				g_item.cout_pickup++; gameUser.pickup(); g_item.last_PickupTime = dNow;
			}
		}
		if (!bNeedGoCenter)
		{
			switch (loopcount % 4)
			{
			case 0:	gameUser.move_top_one(); break;
			case 1: gameUser.move_right_one(); break;
			case 2: gameUser.move_down_one(); break;
			case 3: gameUser.move_left_one(); break;
			}
		}
		Sleep(50);
		//gameUser.ALT_Up();



	}
}


void CGuaGua2Dlg::OnBnClickedRadioF1()
{
}
#include "dll_injector.h"
void CGuaGua2Dlg::OnBnClickedButtonInjection()
{
	int user = m_gameUser.GetCurSel();
	if (user == -1)return;
	auto &gameObj = ProcessFind::getInstance()->gameUserObjs[user];
	CString rstring;
	GetDlgItemText(IDC_BUTTON_INJECTION, rstring);

	
	//获取当前目录
	// 获取路径
	wchar_t pszFilePath[MAX_PATH];
	memset(pszFilePath, 0, sizeof(pszFilePath) * sizeof(char));
	GetModuleFileName(NULL, pszFilePath, MAX_PATH);

	PathRemoveFileSpec(pszFilePath);
	//PathAppend(pszFilePath, L"Dll1.dll");



	CString dllPath;
	dllPath.Format(L"%s\\hooking_dll_tpl.dll", pszFilePath);

	
	if (rstring == L"注射")
	{
		bool b = Dll_injector::action_load(gameObj.pid, dllPath.GetString());
		CString x;
		x.Format(L"%s %s", rstring, b ? L"成功" : L"失败");
		AfxMessageBox(x);

		g_Sharemem = new Sharemem();
		g_Sharemem->CreateSharemem(gameObj.pid);
		rstring = L"反注射";
	}
	else {
		bool b=Dll_injector::action_unload(gameObj.pid, dllPath.GetString());
		CString x;
		x.Format(L"%s %s", rstring, b ? L"成功" : L"失败");
		AfxMessageBox(x);
		delete g_Sharemem;
		rstring = L"注射";
	}
	SetDlgItemText(IDC_BUTTON_INJECTION, rstring);
}


void CGuaGua2Dlg::OnBnClickedButtonNp()
{
	int user = m_gameUser.GetCurSel();
	if (user == -1)return;
	auto& gameObj = ProcessFind::getInstance()->gameUserObjs[user];
	gameObj.Press5_forNP();
}
