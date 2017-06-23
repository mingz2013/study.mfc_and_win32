
// ServerDlg.h : ͷ�ļ�
//

#pragma once


// CServerDlg �Ի���
class CServerDlg : public CDialogEx
{
// ����
public:
	CServerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_SERVER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonListen();
	afx_msg void OnBnClickedButtonSend();

	static UINT __cdecl ThreadProc( LPVOID pParam );
	SOCKET m_SockListen, m_SockClient;
	void ShowMsg(CString strMsg);
	BOOL WinSockInit();
	BOOL SOCKET_Select(SOCKET hSocket, int nTimeOut = 100, BOOL bRead = TRUE);
};
