
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

#include <thread>



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
	//	DDX_Control(pDX, IDC_COMBO_GAMEUSER, m_gameUser);
	DDX_Control(pDX, IDC_SLIDER_POSOFFSET, m_posOffset);
	DDX_Control(pDX, IDC_SLIDER_POSOFFSET2, m_posOffset2);
	DDX_Radio(pDX, IDC_RADIO_F1, m_mainFuncType);
	DDX_Control(pDX, IDC_RADIO_F1, m_radio_FUN);
	DDX_Control(pDX, IDC_LIST1, m_logListBox);
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
	//ON_CBN_SELCHANGE(IDC_COMBO_GAMEUSER, &CGuaGua2Dlg::OnCbnSelchangeComboGameuser)
	ON_BN_CLICKED(IDCANCEL, &CGuaGua2Dlg::OnBnClickedCancel)
	//ON_BN_CLICKED(IDC_BUTTON_REFRESH, &CGuaGua2Dlg::OnBnClickedButtonRefresh)
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
	ON_BN_CLICKED(IDC_CHECK_ALT, &CGuaGua2Dlg::OnBnClickedCheckAlt)
	ON_BN_CLICKED(IDC_BUTTON_KILLTASK, &CGuaGua2Dlg::OnBnClickedButtonKilltask)
	ON_BN_CLICKED(IDC_CHECK_LEFTCLICK, &CGuaGua2Dlg::OnBnClickedCheckLeftclick)
	ON_BN_CLICKED(IDC_CHECK_PRESSK, &CGuaGua2Dlg::OnBnClickedCheck2)
END_MESSAGE_MAP()


// CGuaGua2Dlg 消息处理程序

#include "mouseHook.h"
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
	
	SetDlgItemText(IDC_STATIC_CURUSER,g_currentGameObj->titlename);
	
	//OnBnClickedButtonRefresh();
	m_posOffset.SetRange(0, 5);
	m_posOffset2.SetRange(0, 50);
	m_posOffset2.SetPos(40);

	OnCbnSelchangeComboGameuser();
	m_posOffset.SetPos(1);
	SetTimer(timer_updateGPS, 1000, NULL);

#ifdef DEBUG
	GetDlgItem(ID_BUTTON_READMEM)->EnableWindow(false);
	GetDlgItem(IDC_CHECK_LEFTCLICK)->EnableWindow(false);
	GetDlgItem(IDC_CHECK_ALT)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON_INJECTION)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON_NP)->EnableWindow(false);
#endif
	
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

	g_currentGameObj->m_ConfigItem.areaOffset = m_posOffset.GetPos();
	g_currentGameObj->setCurrentGPS_To_Setting();
	gpsText.Format(L"%d,%d", g_currentGameObj->settingGPSX, g_currentGameObj->settingGPSY);
	SetDlgItemText(IDC_STATIC_centerPOS, gpsText);

	gpsText.Format(L"%d,%d", g_currentGameObj->settingGPSX - g_currentGameObj->m_ConfigItem.areaOffset, g_currentGameObj->settingGPSY - g_currentGameObj->m_ConfigItem.areaOffset);
	SetDlgItemText(IDC_STATIC_X1Y1, gpsText);

	gpsText.Format(L"%d,%d", g_currentGameObj->settingGPSX + g_currentGameObj->m_ConfigItem.areaOffset, g_currentGameObj->settingGPSY - g_currentGameObj->m_ConfigItem.areaOffset);
	SetDlgItemText(IDC_STATIC_X2Y2, gpsText);

	gpsText.Format(L"%d,%d", g_currentGameObj->settingGPSX + g_currentGameObj->m_ConfigItem.areaOffset, g_currentGameObj->settingGPSY + g_currentGameObj->m_ConfigItem.areaOffset);
	SetDlgItemText(IDC_STATIC_X3Y3, gpsText);

	gpsText.Format(L"%d,%d", g_currentGameObj->settingGPSX - g_currentGameObj->m_ConfigItem.areaOffset, g_currentGameObj->settingGPSY + g_currentGameObj->m_ConfigItem.areaOffset);
	SetDlgItemText(IDC_STATIC_X4Y4, gpsText);


	SetDlgItemInt(IDC_STATIC_XY_OFFSET, g_currentGameObj->m_ConfigItem.areaOffset);
}


void CGuaGua2Dlg::OnNMReleasedcaptureSliderPosoffset(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	OnBnClickedButtonSetcenterpos();

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
		ConfigItem item;
		item.name = g_currentGameObj->titlename;

		Config c;
		c.load(item);

		SetDlgItemInt(IDC_EDIT_TIME_PICKUP, item.pickupTime);
		SetDlgItemInt(IDC_EDIT_TIME_F1, item.f1Time);
		SetDlgItemInt(IDC_EDIT_TIME_F2, item.f2Time);
		SetDlgItemInt(IDC_EDIT_TIME_F3, item.f3Time);
		SetDlgItemInt(IDC_EDIT_TIME_F4, item.f4Time);
		SetDlgItemInt(IDC_EDIT_TIME_F5, item.f5Time);
		SetDlgItemInt(IDC_EDIT_TIME_F6, item.kTime);
		m_mainFuncType = item.mainFunc;

		m_posOffset.SetPos(item.areaOffset);
		m_posOffset2.SetPos(item.stepOffset);
		CheckDlgButton(IDC_CHECK_NP, item.NP);
		CheckDlgButton(IDC_CHECK_ATTACK, item.attack);
		CheckDlgButton(IDC_CHECK_PICKUP, item.pickup);


		g_currentGameObj->m_ConfigItem = item;
		UpdateData(false);
		UpdateData(true);



	}
}
void CGuaGua2Dlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码	
	UpdateData(true);

	ConfigItem item;
	item.name = g_currentGameObj->titlename;
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
	item.kTime = GetDlgItemInt(IDC_EDIT_TIME_F6);
	item.mainFunc = m_mainFuncType;
	item.bPressK = IsDlgButtonChecked(IDC_CHECK_PRESSK);

	item.stepOffset = m_posOffset2.GetPos();
	Config c;
	c.save(item);

	g_currentGameObj->m_ConfigItem = item;

}
bool g_bExit = false;
UINT64 g_count = 0;
void CGuaGua2Dlg::OnBnClickedButtonStart()
{
	CString rtext;
	GetDlgItemText(IDC_BUTTON_START, rtext);
	if (rtext == L"开始") {
		g_bExit = false;
		rtext = L"停止";
		if (g_currentGameObj == nullptr)return;
		{
			m_posOffset2.SetRange(0, (g_currentGameObj->rect.bottom - g_currentGameObj->rect.top) / 2);
		}
		g_currentGameObj->startWork([&](CString& x) {
			if (g_bExit)return;
			CString logstr;
			CTime t1 = CTime::GetCurrentTime();
			logstr.Format(_T("%s %s"), t1.Format(L"%M:%S"), x);
			m_logListBox.InsertString(0,logstr);

			while (m_logListBox.GetCount() > 20)
				m_logListBox.DeleteString(20);

			if (g_count > 100)g_count = 0;
			});
		
	}
	else {
		g_bExit = true;
		rtext = L"开始";
		g_currentGameObj->stop();

	}
	SetDlgItemText(IDC_BUTTON_START, rtext);
}


void CGuaGua2Dlg::OnBnClickedCancel()
{
	g_bExit = true;
	for (int i=0;i< ProcessFind::getInstance()->gameUserObjs.size();i++)
	{
		ProcessFind::getInstance()->gameUserObjs[i]->stop();
	}

	OnCancel();
}

void CGuaGua2Dlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == timer_updateGPS)
	{
		if (g_currentGameObj)
		{
			loadNP();

			
		}
	}

	CDialogEx::OnTimer(nIDEvent);
}


void CGuaGua2Dlg::OnBnClickedButtonTop()
{

	if (g_currentGameObj == nullptr)return;


	g_currentGameObj->move_top_one();

}


void CGuaGua2Dlg::OnBnClickedButtonTopLeft()
{

	if (g_currentGameObj == nullptr)return;


	g_currentGameObj->move_top_one();
	g_currentGameObj->move_left_one();
}


void CGuaGua2Dlg::OnBnClickedButtonTopRight()
{

	if (g_currentGameObj == nullptr)return;

	g_currentGameObj->move_top_one();
	g_currentGameObj->move_right_one();
}


void CGuaGua2Dlg::OnBnClickedButtonLeft()
{

	if (g_currentGameObj == nullptr)return;


	g_currentGameObj->move_left_one();
}


void CGuaGua2Dlg::OnBnClickedButtonRight()
{

	if (g_currentGameObj == nullptr)return;


	g_currentGameObj->move_right_one();
}


void CGuaGua2Dlg::OnBnClickedButtonDownLeft()
{

	if (g_currentGameObj == nullptr)return;


	g_currentGameObj->move_down_one();
	g_currentGameObj->move_left_one();
}


void CGuaGua2Dlg::OnBnClickedButtonDown()
{

	if (g_currentGameObj == nullptr)return;

	g_currentGameObj->move_down_one();
}


void CGuaGua2Dlg::OnBnClickedButtonDownRight()
{

	if (g_currentGameObj == nullptr)return;

	g_currentGameObj->turn_map();
	return;
	g_currentGameObj->move_down_one();
	g_currentGameObj->move_right_one();
}


void CGuaGua2Dlg::OnBnClickedButtonPickup()
{

	if (g_currentGameObj == nullptr)return;




	g_currentGameObj->doPickup();
}


void CGuaGua2Dlg::OnBnClickedButtonAttack()
{

	if (g_currentGameObj == nullptr)return;


	g_currentGameObj->attackCenter();
}




void CGuaGua2Dlg::OnBnClickedButtonRefresh()
{
	// TODO: 在此添加控件通知处理程序代码


}


void CGuaGua2Dlg::OnBnClickedButtonReadmem()
{
}
void CGuaGua2Dlg::loadNP()
{
	if (!g_currentGameObj)
		return;
	int currentGPSX, currentGPSY;
	g_currentGameObj->hsn.getGPS(currentGPSX, currentGPSY);
	CString gpsText;
	gpsText.Format(L"%d/%d", currentGPSX, currentGPSY);


	SetDlgItemText(IDC_STATIC_CurrentPOS, gpsText);

	CString ss;


	UpdateData(true);
	ss.Format(_T("%s %I64d>>   altdown:%d"),
		g_currentGameObj->titlename, g_currentGameObj->loopcount,		
		g_currentGameObj->bAltDown());
	SetWindowText(ss);


	g_currentGameObj->hsn.doRead();
	CString s;
	s.Format(L"NP:%d/%d", g_currentGameObj->hsn.info.np, g_currentGameObj->hsn.info.npMax);
	SetDlgItemText(IDC_STATIC_NP, s);

	s.Format(L"HP:%d/%d", g_currentGameObj->hsn.info.HP, g_currentGameObj->hsn.info.HPMax);
	SetDlgItemText(IDC_STATIC_HP, s);


	s.Format(L"SP:%d/%d", g_currentGameObj->hsn.info.sp, g_currentGameObj->hsn.info.spMax);
	SetDlgItemText(IDC_STATIC_SP, s);

	SetDlgItemInt(IDC_STATIC_PICKUP, g_currentGameObj->m_ConfigItem.cout_pickup);
	SetDlgItemInt(IDC_STATIC_F1, g_currentGameObj->m_ConfigItem.cout_f1);
	SetDlgItemInt(IDC_STATIC_F2, g_currentGameObj->m_ConfigItem.cout_f2);
	SetDlgItemInt(IDC_STATIC_F3, g_currentGameObj->m_ConfigItem.cout_f3);
	SetDlgItemInt(IDC_STATIC_F4, g_currentGameObj->m_ConfigItem.cout_f4);
	SetDlgItemInt(IDC_STATIC_F5, g_currentGameObj->m_ConfigItem.cout_f5);
	SetDlgItemInt(IDC_STATIC_F6, g_currentGameObj->m_ConfigItem.cout_k);

	SetDlgItemText(IDC_STATIC_GOCENTERINFO, g_currentGameObj->g_GoCenterInfo);

	g_currentGameObj->m_ConfigItem.stepOffset = m_posOffset2.GetPos();

	gpsText.Format(L"设置:%d/%d 偏移%d \r\n当前:%d/%d", 
		g_currentGameObj->settingGPSX, g_currentGameObj->settingGPSY,
		g_currentGameObj->m_ConfigItem.areaOffset, 
		currentGPSX, currentGPSY);
	SetDlgItemText(IDC_STATIC_XY_OFFSET, gpsText);

}


void CGuaGua2Dlg::OnBnClickedButtonShowwindow()
{

	if (g_currentGameObj == nullptr)
	{
		return;
	}

	HWND hwnd = g_currentGameObj->hWnd;
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



void CGuaGua2Dlg::OnBnClickedRadioF1()
{
}
#include "dll_injector.h"
void CGuaGua2Dlg::OnBnClickedButtonInjection()
{

	if (g_currentGameObj == nullptr)return;

	CString rstring;
	GetDlgItemText(IDC_BUTTON_INJECTION, rstring);

	if (rstring == L"注射")
	{
		g_currentGameObj->InjectDll(true);
		rstring = L"反注射";
	}
	else
	{
		g_currentGameObj->InjectDll(false);
		rstring = L"注射";
	}
	

	
	SetDlgItemText(IDC_BUTTON_INJECTION, rstring);
}


void CGuaGua2Dlg::OnBnClickedButtonNp()
{
	if (g_currentGameObj == nullptr)return;
	g_currentGameObj->turn_map();
}


void CGuaGua2Dlg::OnBnClickedCheckAlt()
{
	if (g_currentGameObj == nullptr )return;
	if (IsDlgButtonChecked(IDC_CHECK_ALT))
		g_currentGameObj->PressAlt(true);
	else
		g_currentGameObj->PressAlt(false);
}


void CGuaGua2Dlg::OnBnClickedButtonKilltask()
{
	if (g_currentGameObj == nullptr)return;

	HANDLE hProcess;
	hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, g_currentGameObj->pid);
	//结束进程
	BOOL bResult = false;
	if (hProcess)
		bResult = TerminateProcess(hProcess, 0);
	OnBnClickedButtonRefresh();
}


void CGuaGua2Dlg::OnBnClickedCheckLeftclick()
{
	if (g_currentGameObj == nullptr)return;

	//g_currentGameObj->enableLeftClick(IsDlgButtonChecked(IDC_CHECK_LEFTCLICK));
}


void CGuaGua2Dlg::OnBnClickedButtonSplit()
{
	
}
void CGuaGua2Dlg::OnBnClickedButtonSplit2()
{

}


void CGuaGua2Dlg::OnBnClickedCheck2()
{
	g_currentGameObj->m_ConfigItem.bPressK = IsDlgButtonChecked(IDC_CHECK_PRESSK);
}
