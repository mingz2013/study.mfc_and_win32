#pragma once
#define MAX_BUF_SIZE 1024
#define WM_TRAYICON_MSG (WM_USER + 100) // ��Ϣ���Զ������Ϣ�����ݸ�����
class CChatRoomDlg;

class CClientItem
{
public:
	CString m_strIp;
	SOCKET m_Socket;
	HANDLE hThread;
	CChatRoomDlg *m_pMainWnd;
	CClientItem(){
	
		m_pMainWnd = NULL;
		m_Socket = INVALID_SOCKET;
		hThread = NULL;
	}
};

/*
DWORD WINAPI ListenThreadFunc(LPVOID pParam);

BOOL SOCKET_Select(SOCKET hSocket, int nTimeOut, BOOL bRead);
*/