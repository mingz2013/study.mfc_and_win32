#pragma once


// CPASSWD �Ի���

class CPASSWD : public CDialogEx
{
	DECLARE_DYNAMIC(CPASSWD)

public:
	CPASSWD(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPASSWD();

// �Ի�������
	enum { IDD = IDD_DIALOG_PASS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonOk();
//	CString m_password;
};
