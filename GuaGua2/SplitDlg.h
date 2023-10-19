#pragma once
#include "afxdialogex.h"


// CSplitDlg 对话框

class CSplitDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSplitDlg)

public:
	CSplitDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CSplitDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SPLITDLG	};
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
};
