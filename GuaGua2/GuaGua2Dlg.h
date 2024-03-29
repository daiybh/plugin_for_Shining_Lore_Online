﻿
// GuaGua2Dlg.h: 头文件
//

#pragma once
#include <thread>

// CGuaGua2Dlg 对话框
class CGuaGua2Dlg : public CDialogEx
{
// 构造
public:
	CGuaGua2Dlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GUAGUA2_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonSetcenterpos();
	afx_msg void OnTRBNThumbPosChangingSliderPosoffset(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedCheckNp();
	afx_msg void OnBnClickedCheckPickup();
	afx_msg void OnBnClickedCheckAttack();
	afx_msg void OnBnClickedOk();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButtonTop();
	afx_msg void OnBnClickedButtonTopLeft();
	afx_msg void OnBnClickedButtonTopRight();
	afx_msg void OnBnClickedButtonLeft();
	afx_msg void OnBnClickedButtonRight();
	afx_msg void OnBnClickedButtonDownLeft();
	afx_msg void OnBnClickedButtonDown();
	afx_msg void OnBnClickedButtonDownRight();
	afx_msg void OnBnClickedButtonAttack();
	CSliderCtrl m_posOffset;
	afx_msg void OnCbnSelchangeComboGameuser();
	afx_msg void OnBnClickedCancel();
	CSliderCtrl m_posOffset2;
	afx_msg void OnBnClickedButtonRefresh();
	afx_msg void OnBnClickedButtonStart();
	afx_msg void OnNMReleasedcaptureSliderPosoffset(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedButtonReadmem();
	void loadNP();
	afx_msg void OnBnClickedButtonPickup();
	afx_msg void OnBnClickedButtonShowwindow();

	int m_mainFuncType;
	afx_msg void OnBnClickedRadioF1();
	CButton m_radio_FUN;
	afx_msg void OnBnClickedButtonInjection();
	afx_msg void OnBnClickedButtonNp();
	afx_msg void OnBnClickedCheckAlt();
	afx_msg void OnBnClickedButtonKilltask();
	afx_msg void OnBnClickedCheckLeftclick();
	afx_msg void OnBnClickedButtonSplit();
	afx_msg void OnBnClickedButtonSplit2();
	CListBox m_logListBox;
	afx_msg void OnBnClickedCheck2();
	CSliderCtrl m_posOffset3;
};
