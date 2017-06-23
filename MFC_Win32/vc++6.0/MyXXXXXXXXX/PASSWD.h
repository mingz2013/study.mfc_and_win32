#if !defined(AFX_PASSWD_H__FD3E9AE3_994D_421A_BDEF_A9DD710BEB98__INCLUDED_)
#define AFX_PASSWD_H__FD3E9AE3_994D_421A_BDEF_A9DD710BEB98__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PASSWD.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPASSWD dialog

class CPASSWD : public CDialog
{
// Construction
public:
	CPASSWD(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPASSWD)
	enum { IDD = IDD_PASSWORD };
	CString	m_password;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPASSWD)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPASSWD)
	afx_msg void OnSendPassword();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PASSWD_H__FD3E9AE3_994D_421A_BDEF_A9DD710BEB98__INCLUDED_)
