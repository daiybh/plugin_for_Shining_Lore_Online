#pragma once
#include "afxdialogex.h"


// CSelectUserDlg 对话框

class CSelectUserDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSelectUserDlg)

public:
	CSelectUserDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CSelectUserDlg();
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SELECTUSER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_gameUser;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedOk();
};
