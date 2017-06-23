
// GroupWinsockDlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// CGroupWinsockDlg 对话框
class CGroupWinsockDlg : public CDialogEx
{
// 构造
public:
	CGroupWinsockDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_GROUPWINSOCK_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonAdd();
	CEdit m_GroupIP;
	CEdit m_Show;
	SOCKET s;
	void ShowMsg(CString strMsg);
	static DWORD WINAPI ClientThreadProc(LPVOID lpParameter);
	BOOL SOCKET_Select(SOCKET hSocket, int nTimeOut, BOOL bRead);
	struct ip_mreq ipmr;
	SOCKADDR_IN local,from,remote;
	int len;
	HANDLE m_hThread;
	//CGroupWinsockDlg *m_pMainWnd;
	afx_msg void OnBnClickedButtonSend();
};
