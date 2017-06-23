
// MyDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"

//#define port 12345
// CMyDlg 对话框
class CMyDlg : public CDialogEx
{
// 构造
public:
	CMyDlg(CWnd* pParent = NULL);	// 标准构造
	

// 对话框数据
	enum { IDD = IDD_MY_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	CImageList m_ImageList;
	CImageList m_ImageList_Tree;
	HTREEITEM m_hRoot;
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CTreeCtrl m_TreeCtrl;
	afx_msg void OnBnClickedButtonConn();
	WSADATA wsadata;
	SOCKET server;
	sockaddr_in serveraddr;
//	CEdit m_Edit;
	//CString m_addr;
//	CString m_addr;
//	CEdit m_Edit;
	CListCtrl	m_list;
	CTreeCtrl	m_tree;
	CString	m_addr;
	static void SetPubDir(CString path);
	int GetDriverProc(BYTE* DATE);
};
