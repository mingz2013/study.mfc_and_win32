#pragma once
#include "stdafx.h"
class CMySocket
{
public:
	CMySocket(void);
	~CMySocket(void);

	int MyRecv(SOCKET socket,char* buf,int bytes);
	int MySend(SOCKET socket,const char* buf,int bytes);
	SOCKET StartSocket(char Address[160]);
	int m_port;
};

