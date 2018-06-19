#if !defined(AFX_CQMPLUGIN_H__8D2C77FD_C8DC_41F9_99CC_03084B9C4310__INCLUDED_)
#define AFX_CQMPLUGIN_H__8D2C77FD_C8DC_41F9_99CC_03084B9C4310__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CQMPlugin.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CQMPlugin command target

class CQMPlugin : public CCmdTarget
{
	DECLARE_DYNCREATE(CQMPlugin)

	CQMPlugin();           // protected constructor used by dynamic creation

// Attributes
public:
	struct DESCRIPTION_LIST
	{
		char *m_lpszItemName;
		char *m_lpszDescription;
		char *m_lpszInterpretTemplate;
	};

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQMPlugin)
	public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CQMPlugin();
	afx_msg BSTR GetPluginDescription(LPCTSTR bstrItemName);
	afx_msg BSTR GetPluginInterpretTemplate(LPCTSTR bstrItemName);

	// Generated message map functions
	//{{AFX_MSG(CQMPlugin)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_OLECREATE(CQMPlugin)
	DECLARE_MESSAGE_MAP()

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CQMPlugin)
	afx_msg long WriteINI(LPCTSTR lpszSectionName, LPCTSTR lpszKeyName, LPCTSTR lpszBuffer, LPCTSTR lpszINIFilePath);
	afx_msg BSTR ReadINI(LPCTSTR lpszSectionName, LPCTSTR lpszKeyName, LPCTSTR lpszINIFilePath);
	afx_msg long CopyFile(LPCTSTR lpszSourceFile, LPCTSTR lpszTargetFile);
	afx_msg BOOL IsFileExit(LPCTSTR lpszSourceFile);
	afx_msg long DeleteFile(LPCTSTR FileName);
	afx_msg long MoveFile(LPCTSTR lpszSourceFile, LPCTSTR lpszTargetFile);
	afx_msg long CreateFolder(LPCTSTR lpszDirectory);
	afx_msg long DeleteFolder(LPCTSTR lpszDirectory);
	afx_msg long ReNameFile(LPCTSTR oldName,LPCTSTR newName);
	afx_msg BOOL SetAttrib(LPCTSTR lpszFilePath, BOOL Sign);
	afx_msg long SetDate(LPCTSTR lpszFileName, LPCTSTR lpLastWriteTime);
	afx_msg long GetFileLength(LPCTSTR lpszFileName);
	afx_msg BSTR SelectFile();
	afx_msg BSTR SelectDirectory();
	afx_msg long SeekFile(long lpszHandle, long lpszOffset);
	afx_msg BSTR ReadLine(long hFile);
	afx_msg long WriteLine(long lpszHandle, LPCTSTR lpszWriteContent);
	afx_msg BSTR ReadFileEx(LPCTSTR lpszFileName);
	afx_msg long WriteFileEx(LPCTSTR lpszFileName, LPCTSTR lpszBeWrite);
	afx_msg BSTR ReadFile(long lpszHandle, long lpszReadLength);
	afx_msg long WriteFile(long lpszHandle, LPCTSTR lpszWriteContent);
	afx_msg long ExistFile(LPCTSTR FileAttr);
	afx_msg long OpenFile(LPCTSTR FileName);
	afx_msg long CloseFile(long hwd);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()

private:
	static DESCRIPTION_LIST m_DescriptionList[];
	static const int m_iDescriptionListSize;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CQMPLUGIN_H__8D2C77FD_C8DC_41F9_99CC_03084B9C4310__INCLUDED_)
