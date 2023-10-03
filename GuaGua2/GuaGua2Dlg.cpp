
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
std::thread g_thread;
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
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGuaGua2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_GAMEUSER, m_gameUser);
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
	ON_BN_CLICKED(IDC_BUTTON_REFRESH, &CGuaGua2Dlg::OnBnClickedButtonRefresh)
	ON_BN_CLICKED(IDC_BUTTON_START, &CGuaGua2Dlg::OnBnClickedButtonStart)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_POSOFFSET, &CGuaGua2Dlg::OnNMReleasedcaptureSliderPosoffset)
	ON_BN_CLICKED(ID_BUTTON_READMEM, &CGuaGua2Dlg::OnBnClickedButtonReadmem)
	ON_BN_CLICKED(IDC_BUTTON_PICKUP, &CGuaGua2Dlg::OnBnClickedButtonPickup)
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
	// TODO: 在此添加控件通知处理程序代码
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
		m_posOffset2.SetPos(item.stepOffset);
		CheckDlgButton(IDC_CHECK_NP, item.NP);
		CheckDlgButton(IDC_CHECK_ATTACK, item.attack);
		CheckDlgButton(IDC_CHECK_PICKUP, item.pickup);
		g_item = item;


		int pid = ProcessFind::getInstance()->gameUserObjs[user].pid;

		hsn.open(pid);


	}
}
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

}
bool bNeedGoCenter = false;

CString goto_Center(GameObj& curGameUser,int x1, int y1, int x4, int y4)
{
	CString  showText;
	if (currentGPSX < x1)
	{
		if (currentGPSY < y1)
		{
			showText = L"小于 x1 y1 往左下走";
			curGameUser.move_left_down_one(); bNeedGoCenter = true;
		}
		else if (currentGPSY > y4)
		{
			showText = L"超出 x1 y4  往左上走";
			curGameUser.move_left_top_one(); bNeedGoCenter = true;
		}
		else
		{
			showText = L"x1 超出 y 没有超出 往左";
			curGameUser.move_left_one(); bNeedGoCenter = true;
		}
	}
	else if (currentGPSX > x1 && currentGPSX < x4)
	{
		if (currentGPSY < y1)
		{
			showText = L"x1 没超出 y1 小了 往下走";
			curGameUser.move_down_one(); bNeedGoCenter = true;
		}
		else if (currentGPSY > y4)
		{
			showText = L"x1 没超出 y1 大了 往上走";
			curGameUser.move_top_one(); bNeedGoCenter = true;
		}
	}
	else if (currentGPSX > x4)
	{
		if (currentGPSY < y1)
		{
			showText = L"小于 x1 y1 往右下走";
			curGameUser.move_right_down_one(); bNeedGoCenter = true;
		}
		else if (currentGPSY > y4)
		{
			showText = L"超出 x1 y4  往右上走";
			curGameUser.move_right_top_one(); bNeedGoCenter = true;
		}
		else
		{
			showText = L"x1 超出 y 没有超出 往右走";
			curGameUser.move_right_one(); bNeedGoCenter = true;
		}
	}

	else if (currentGPSY < y1)
	{
		if (currentGPSX < x1)
		{
			showText = L"小于x1  往左下走";
			curGameUser.move_left_down_one(); bNeedGoCenter = true;
		}
		else if (currentGPSX > x4)
		{
			showText = L"大于x4  往右下走";
			curGameUser.move_right_down_one(); bNeedGoCenter = true;
		}
		else
		{
			showText = L"y1 超出 x 没有超出 往下";
			curGameUser.move_down_one(); bNeedGoCenter = true;
		}
	}
	else if (currentGPSY > y4)
	{
		if (currentGPSX < x1)
		{
			showText = L"小于x1  往左上走";
			curGameUser.move_left_top_one(); bNeedGoCenter = true;
		}
		else if (currentGPSX > x4)
		{
			showText = L"大于x4  往右上走";
			curGameUser.move_right_top_one(); bNeedGoCenter = true;
		}
		else
		{
			showText = L"y1 超出 x 没有超出 往上";
			curGameUser.move_top_one(); bNeedGoCenter = true;
		}
	}
	else if (currentGPSY > y1 && currentGPSY < y4)
	{
		if (currentGPSX < x1)
		{
			showText = L"小于x1  往左走";
			curGameUser.move_left_one(); bNeedGoCenter = true;
		}
		else if (currentGPSX > x4)
		{
			showText = L"大于x1  往右走";
			curGameUser.move_right_one(); bNeedGoCenter = true;
		}
	}
	return showText;
}
CString  checkIfoutGPS(GameObj& curGameUser)
{
	if (settingGPSX == 0 && settingGPSY == 0)
	{
		return L"中心点还没设置";
	}
	if (currentGPSX == 0 && currentGPSX == 0)
	{
		return L"当前坐标未获取到";
	}


	if (currentGPSX == settingGPSX && currentGPSY == settingGPSY)
	{
		bNeedGoCenter = false;
		return L"已经在设置坐标点";
	}
	int offset = g_item.areaOffset;

	if (bNeedGoCenter)
	{
		offset = 0;
	}
	return goto_Center(curGameUser, settingGPSX - offset, settingGPSY - offset, settingGPSX + offset, settingGPSY + offset);
}

void CGuaGua2Dlg::OnBnClickedButtonStart()
{
	CString rtext;
	GetDlgItemText(IDC_BUTTON_START, rtext);
	if (rtext == "开始") {
		rtext = "停止";
		g_thread = std::thread([&]()
			{
				loopcount = 0;
				bExit = false;
				bool bSetRange = false;
				while (!bExit)
				{
					DWORD dt = WaitForSingleObject(g_event, 1000);
					if (dt == WAIT_OBJECT_0)break;




					hsn.getGPS(currentGPSX, currentGPSY);

					int user = m_gameUser.GetCurSel();
					if (user != -1)
					{
						GameObj& gameUser = ProcessFind::getInstance()->gameUserObjs[user];

						CString x = checkIfoutGPS(gameUser);
						SetDlgItemText(IDC_STATIC_GOCENTERINFO, x);
						if (!bSetRange)
						{
							m_posOffset2.SetRange(0, (gameUser.rect.bottom - gameUser.rect.top) / 2);
							bSetRange = true;
						}
						g_item.stepOffset = m_posOffset2.GetPos();

						gameUser.move_one_offset = g_item.stepOffset;

						gameUser.ALT_Down();
						uint64_t dNow = GetTickCount();
						if (g_item.pickup)
						{
							if (g_item.pickupTime>0 && (dNow - g_item.last_PickupTime > g_item.pickupTime * 1000))
							{
								g_item.cout_pickup++; gameUser.pickup(); g_item.last_PickupTime = dNow;
							}
						}
						if (g_item.attack)
						{
							if (g_item.f1Time>0 && (dNow - g_item.last_f1Time > g_item.f1Time * 1000))
							{
								g_item.cout_f1++; gameUser.F1(); g_item.last_f1Time = dNow; gameUser.attackCenter();
							}
							if (g_item.f2Time>0 && (dNow - g_item.last_f2Time > g_item.f2Time * 1000))
							{
								g_item.cout_f2++; gameUser.F2(); g_item.last_f2Time = dNow; gameUser.F1(); gameUser.attackCenter();
							}
							if (g_item.f3Time>0 && (dNow - g_item.last_f3Time > g_item.f3Time * 1000))
							{
								g_item.cout_f3++; gameUser.F3(); g_item.last_f3Time = dNow; gameUser.F1(); gameUser.attackCenter();
							}
							if (g_item.f4Time >0 &&(dNow - g_item.last_f4Time > g_item.f4Time * 1000))
							{
								g_item.cout_f4++; gameUser.F4(); g_item.last_f4Time = dNow; gameUser.F1(); gameUser.attackCenter();
							}
							if (g_item.f5Time > 0 && (dNow - g_item.last_f5Time > g_item.f5Time * 1000))
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
						Sleep(50);
						//gameUser.ALT_Up();
					}

					loopcount++;
				}
				loopcount = 9999999999999999999;
			});

	}
	else {
		rtext = "开始";
		bExit = true;
		g_event.SetEvent();
		if (g_thread.joinable())
			g_thread.join();
	}
	SetDlgItemText(IDC_BUTTON_START, rtext);
}


void CGuaGua2Dlg::OnBnClickedCancel()
{
	bExit = true;
	g_event.SetEvent();
	if (g_thread.joinable())
		g_thread.join();
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


	ProcessFind::getInstance()->gameUserObjs[user].pickup();
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
	loadNP();
}
void CGuaGua2Dlg::loadNP()
{
	{
		hsn.getGPS(currentGPSX, currentGPSY);
		CString gpsText;
		gpsText.Format(L"%d/%d", currentGPSX, currentGPSY);
		

		SetDlgItemText(IDC_STATIC_CurrentPOS, gpsText);
		CString ss;
		ss.Format(_T("%d>>user:%d gps:%d [%d]"), loopcount, m_gameUser.GetCurSel(), currentGPSX, currentGPSY);
		SetWindowText(ss);


	}

	hsn.doRead();
	CString s;
	s.Format(L"%d/%d", hsn.info.np, hsn.info.npMax);
	SetDlgItemText(IDC_STATIC_NP, s);
}
