#pragma once

#include "MySocket.h"
class CItemData
{
public:
	CItemData(UINT id,SOCKET sock,SOCKADDR_IN *addr,HWND m_hWnd);
	~CItemData(void);

	UINT m_id;
    
    SOCKET GetSocket();
    CString m_IP;
    CString m_Address;
    CString m_OS;
    CString m_Ver;
    bool Cam;

	SOCKET m_sock;
	void Run();
    void OnBeginListen();
    CMySocket m_Mysocket;
    HWND m_hWnd;
	static DWORD WINAPI CItemData::OnListen(LPVOID lp);
};

