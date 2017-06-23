#pragma once
#include "MySocket.h"
#include "Conmmon.h"
#include "FileDlg.h"
class CItemData : public CDialog
{
public:
	CItemData(UINT id,SOCKET sock,SOCKADDR_IN *addr,HWND m_hWnd);
	~CItemData(void);
	

    UINT m_id;
    void Run();
    SOCKET GetSocket();
    CString m_IP;
    CString m_Address;
    CString m_OS;
    CString m_Ver;
    bool Cam;
	void RunToFileManager();
	CFileDlg* m_filedlg;
private:
	SOCKET m_sock;
    void OnBeginListen();
    CMySocket m_Mysocket;
    HWND m_hWnd;
	static DWORD WINAPI OnListen(LPVOID lp);
	void GetSysVer(SYSTEMINFO sys);
	
};

