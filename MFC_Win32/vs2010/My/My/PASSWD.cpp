// PASSWD.cpp : 实现文件
//

#include "stdafx.h"
#include "My.h"
#include "PASSWD.h"
#include "afxdialogex.h"
#include "MyDlg.h"


// CPASSWD 对话框

IMPLEMENT_DYNAMIC(CPASSWD, CDialogEx)

CPASSWD::CPASSWD(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPASSWD::IDD, pParent)
	//, m_password(_T(""))
{
	//  m_password = _T("");
}

CPASSWD::~CPASSWD()
{
}

void CPASSWD::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Text(pDX, IDC_EDIT_PASS, m_password);
	//DDX_Text(pDX, IDC_EDIT_PASS, m_password);
}


BEGIN_MESSAGE_MAP(CPASSWD, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_OK, &CPASSWD::OnBnClickedButtonOk)
END_MESSAGE_MAP()


// CPASSWD 消息处理程序


void CPASSWD::OnBnClickedButtonOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//UpdateData(true);// 为true,把控件的值传给成员变量，为false，则相反
	CString m_password;
	GetDlgItemText(IDC_EDIT_PASS, m_password);
	if( m_password.IsEmpty())
	{
		MessageBox(_T("密码不能为空，请输入密码"));
		return;
	}
	CMyDlg::SetPubDir(m_password);
	OnCancel();
}
