#pragma once
class CMySocket
{
public:
	CMySocket(void);
	~CMySocket(void);


	int RecvCommand(SOCKET socket,char* buf,int bytes);
	int SendCommand(SOCKET socket,const char* buf,int bytes);
	void Clean();
};

