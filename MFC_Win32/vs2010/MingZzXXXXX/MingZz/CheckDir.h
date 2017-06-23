#pragma once


// CCheckDir 对话框

class CCheckDir : public CDialogEx
{
	DECLARE_DYNAMIC(CCheckDir)

public:
	CCheckDir(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCheckDir();

// 对话框数据
	enum { IDD = IDD_DIALOG_DIR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	bool flag;
	wchar_t path[260];
};
