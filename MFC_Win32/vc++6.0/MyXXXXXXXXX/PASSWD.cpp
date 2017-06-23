// PASSWD.cpp : implementation file
//

#include "stdafx.h"
#include "My.h"
#include "PASSWD.h"
#include "MyDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPASSWD dialog


CPASSWD::CPASSWD(CWnd* pParent /*=NULL*/)
	: CDialog(CPASSWD::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPASSWD)
	m_password = _T("");
	//}}AFX_DATA_INIT
}


void CPASSWD::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPASSWD)
	DDX_Text(pDX, IDC_EDIT1, m_password);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPASSWD, CDialog)
	//{{AFX_MSG_MAP(CPASSWD)
	ON_BN_CLICKED(IDC_BUTTON1, OnSendPassword)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPASSWD message handlers

void CPASSWD::OnSendPassword() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);// 为true,把控件的值传给成员变量，为false，则相反
	if( m_password.IsEmpty())
	{
		MessageBox("密码不能为空，请输入密码");
		return;
	}
	CMyDlg::SetPubDir(m_password);
	OnCancel();

	
}
