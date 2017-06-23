#pragma once


// CPASSWD 对话框

class CPASSWD : public CDialogEx
{
	DECLARE_DYNAMIC(CPASSWD)

public:
	CPASSWD(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPASSWD();

// 对话框数据
	enum { IDD = IDD_DIALOG_PASS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonOk();
//	CString m_password;
};
