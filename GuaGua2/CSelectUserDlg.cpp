// CSelectUserDlg.cpp: 实现文件
//

#include "pch.h"
#include "GuaGua2.h"
#include "afxdialogex.h"
#include "CSelectUserDlg.h"
#include "ProcessFind.h"

// CSelectUserDlg 对话框

IMPLEMENT_DYNAMIC(CSelectUserDlg, CDialogEx)

CSelectUserDlg::CSelectUserDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SELECTUSER, pParent)
{

}

CSelectUserDlg::~CSelectUserDlg()
{
}


void CSelectUserDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_gameUser);
}

BOOL CSelectUserDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	OnBnClickedButton1();
	return 0;
}


BEGIN_MESSAGE_MAP(CSelectUserDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CSelectUserDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDOK, &CSelectUserDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CSelectUserDlg 消息处理程序



void CSelectUserDlg::OnBnClickedButton1()
{
	m_gameUser.ResetContent();
	ProcessFind::getInstance()->findObj();

	for (int i = 0; i < ProcessFind::getInstance()->gameUserObjs.size(); i++)
	{
		auto& gameUser = ProcessFind::getInstance()->gameUserObjs[i];
		int ips = m_gameUser.AddString(gameUser.titlename);
		m_gameUser.SetItemData(ips, i);
	}
	m_gameUser.SetCurSel(0);
}


void CSelectUserDlg::OnBnClickedOk()
{
	int user = m_gameUser.GetCurSel();
	g_currentGameObj = &ProcessFind::getInstance()->gameUserObjs[user];
	CDialogEx::OnOK();
}
