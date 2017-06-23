
// ClientDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"


// CClientDlg 对话框
class CClientDlg : public CDialogEx
{
// 构造
public:
	CClientDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_CLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_ListClient;
	CStatusBar m_statusbar;// 状态栏
	CRect m_rect;// 矩形对象
	void InitSystem();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	static DWORD WINAPI OninitSocket(LPVOID self);
	bool CClientDlg::InitSocket();
	SOCKET SLisen;
	BOOL SOCKET_Select(SOCKET hSocket, int nTimeOut, BOOL bRead);
	void GetNewItemData(SOCKET sock,SOCKADDR_IN addr);
	UINT m_port;
};
