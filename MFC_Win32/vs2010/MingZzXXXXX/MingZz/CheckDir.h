#pragma once


// CCheckDir �Ի���

class CCheckDir : public CDialogEx
{
	DECLARE_DYNAMIC(CCheckDir)

public:
	CCheckDir(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCheckDir();

// �Ի�������
	enum { IDD = IDD_DIALOG_DIR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	bool flag;
	wchar_t path[260];
};
