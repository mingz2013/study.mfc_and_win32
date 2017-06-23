// MyDlg.h : header file
//

#if !defined(AFX_MYDLG_H__AE218951_9DB4_4244_9FBC_E78C9DDFE7FF__INCLUDED_)
#define AFX_MYDLG_H__AE218951_9DB4_4244_9FBC_E78C9DDFE7FF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMyDlg dialog

class CMyDlg : public CDialog
{
// Construction
public:
	CMyDlg(CWnd* pParent = NULL);	// standard constructor
	static void SetPubDir(CString path);
	int GetDriverProc(BYTE* DATE);

// Dialog Data
	//{{AFX_DATA(CMyDlg)
	enum { IDD = IDD_MY_DIALOG };
	CListCtrl	m_list;
	CTreeCtrl	m_tree;
	CString	m_addr;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	CImageList m_ImageList;
	CImageList m_ImageList_tree;
	HTREEITEM m_hRoot;
	// Generated message map functions
	//{{AFX_MSG(CMyDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	afx_msg void OnSelchangedTree(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYDLG_H__AE218951_9DB4_4244_9FBC_E78C9DDFE7FF__INCLUDED_)
