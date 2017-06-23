#pragma once
#include "resource.h"
#include "afxcmn.h"
#include "MySocket.h"
#include "Conmmon.h"


// CFileTrans 对话框

class CFileTrans : public CDialogEx
{
	DECLARE_DYNAMIC(CFileTrans)

public:
	CFileTrans(CWnd* pParent = NULL, SOCKET sock = NULL);   // 标准构造函数
	virtual ~CFileTrans();

// 对话框数据
	enum { IDD = IDD_DIALOG_FILETRANS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	SOCKET m_sock;
	void OnAddFilelist(int type,wchar_t *path1,wchar_t *path2,wchar_t *size,__int64 *usize);
	void OnFirstTrans();
	static DWORD WINAPI BeginToTrans(LPVOID self);
	CFile *m_file;
	CListCtrl m_list;
	CMySocket m_Mysock;
	CProgressCtrl m_progress;
	bool BeginToWork;
	int Count;
	void UpdateMainFrame();
	void GetFileData(DOWNFILEDATA fi);
	virtual BOOL OnInitDialog();
	CImageList m_transicon;
};
