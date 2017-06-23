#pragma once
#include "MySocket.h"
#include "Common.h"
class CDisk 
{
public:
	CDisk(void);
	~CDisk(void);

	void SendDrivers(SOCKET sock);
	CMySocket m_sock;
	void SendFileList(wchar_t fp[260],SOCKET sock);
	void DownFile(SOCKET sock,wchar_t DownPath[260]);
};

