
// ClientDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"


// CClientDlg �Ի���
class CClientDlg : public CDialogEx
{
// ����
public:
	CClientDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_ListClient;
	CStatusBar m_statusbar;// ״̬��
	CRect m_rect;// ���ζ���
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
