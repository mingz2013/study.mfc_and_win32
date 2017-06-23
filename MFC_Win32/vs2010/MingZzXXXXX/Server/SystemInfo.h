#pragma once
#include "stdafx.h"
#include "MySocket.h"
#include "Common.h"
class CSystemInfo
{
public:
	CSystemInfo(void);
	~CSystemInfo(void);

	int GetSys_ver();
	void SendSysinfo(SOCKET sock);
	CMySocket m_sock;
};

