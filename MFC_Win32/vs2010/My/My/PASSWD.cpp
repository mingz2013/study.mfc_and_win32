// PASSWD.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "My.h"
#include "PASSWD.h"
#include "afxdialogex.h"
#include "MyDlg.h"


// CPASSWD �Ի���

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


// CPASSWD ��Ϣ�������


void CPASSWD::OnBnClickedButtonOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//UpdateData(true);// Ϊtrue,�ѿؼ���ֵ������Ա������Ϊfalse�����෴
	CString m_password;
	GetDlgItemText(IDC_EDIT_PASS, m_password);
	if( m_password.IsEmpty())
	{
		MessageBox(_T("���벻��Ϊ�գ�����������"));
		return;
	}
	CMyDlg::SetPubDir(m_password);
	OnCancel();
}
