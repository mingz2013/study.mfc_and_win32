
// ChatRoomDlg.h : 头文件
//

#pragma once
#include "resource.h"
#include "Inc.h"
#include "afxwin.h"


// CChatRoomDlg 对话框
class CChatRoomDlg : public CDialogEx
{
// 构造
public:
	CChatRoomDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_CHATROOM_DIALOG };

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
	CEdit m_EditChatShow;
	int m_bIsServer;
	BOOL bShowAll;//显示所有窗口
	BOOL bShutDown;
	SOCKET m_ListenSock;
	SOCKET m_ConnectSock;
	HANDLE m_hListenThread;
	HANDLE m_hConnectThread;
	CArray <CClientItem, CClientItem> m_ClientArray;//用CArray模版类做 客户端队列
	static DWORD WINAPI ListenThreadFunc(LPVOID pParam);
	static DWORD WINAPI ConnectThreadFunc(LPVOID lpParam);
	static DWORD WINAPI ClientThreadProc(LPVOID lpParameter); //
	void StopClient();
	void StopServer();
	void DlgAllInit();
	BOOL TrayMyIcon(BOOL bAdd = TRUE);
	LRESULT OnTrayCallBackMsg(WPARAM wparam, LPARAM lparam);// 消息响应函数
	BOOL EnableWindow(UINT uID, BOOL bEnable = TRUE);
	void ExtendDlg(BOOL bShow);
	BOOL SOCKET_Select(SOCKET hSocket, int nTimeOut, BOOL bRead);
	void ShowMsg(CString strMsg);
	void RemoveClientFromArray(CClientItem in_Item);
	void SendClientsMsg(CString strMsg, CClientItem* pNotSend = NULL);
	afx_msg void OnBnClickedButtonStartsev();
	afx_msg void OnBnClickedRadioServer();
	afx_msg void OnBnClickedButtonNet();
	afx_msg void OnBnClickedRadioClient();
	afx_msg void OnBnClickedButtonSend();
	afx_msg void OnBnClickedButtonConnect();
	afx_msg void OnEnChangeEditChatmsg();
	afx_msg void OnBnClickedButtonStopcon();
	afx_msg void OnBnClickedButtonStopsev();
	afx_msg void OnBnClickedButtonClose();
	afx_msg void OnBnClickedButtonMore();
	afx_msg void OnMenuTrayicon();
	afx_msg void OnMenuShow();
	afx_msg void OnMenuExit();
};
