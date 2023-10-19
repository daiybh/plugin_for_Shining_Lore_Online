// SplitDlg.cpp: 实现文件
//

#include "pch.h"
#include "GuaGua2.h"
#include "afxdialogex.h"
#include "SplitDlg.h"
// CSplitDlg 对话框

IMPLEMENT_DYNAMIC(CSplitDlg, CDialogEx)

CSplitDlg::CSplitDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SPLITDLG, pParent)
{

}

CSplitDlg::~CSplitDlg()
{
}

void CSplitDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSplitDlg, CDialogEx)
    ON_BN_CLICKED(IDC_BUTTON1, &CSplitDlg::OnBnClickedButton1)
END_MESSAGE_MAP()

// CSplitDlg 消息处理程序

BOOL CSplitDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

    
	return 0;
}



void CSplitDlg::OnBnClickedButton1()
{
    
    

}
