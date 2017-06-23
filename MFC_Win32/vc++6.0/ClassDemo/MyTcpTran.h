// MyTcpTran.h: interface for the CMyTcpTran class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYTCPTRAN_H__E7F587CC_B65A_45A7_B926_E5F300620311__INCLUDED_)
#define AFX_MYTCPTRAN_H__E7F587CC_B65A_45A7_B926_E5F300620311__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define SOCKETBIND 1   // 表示服务器端监听端口等待连接
#define SOCKETNOBIND 2 // 表示服务器端主动连接客户端
#define SOCKET_TIMEOUT -100 // 套接字超时
#include"winsock2.h"
#include<string>
using namespace std;
#pragma comment (lib,"ws2_32.lib")

socket m_socket; // m代表类中的

class CMyTcpTran  
{
public:
	CMyTcpTran(); // 构造函数
	virtual ~CMyTcpTran(); // 析构函数
public:
	static bool InitSocketLibray(int lowver,int higver); // 初始化Winsock API 链接库文件

public:
	// 初始化socket函数
	SOCKET InitSocket( int SocketType, string strBindIp, u_short BindPort, int opt );
	// 针对本地监听的处理函数
	SOCKET myaccept(SOCKET s, struct sockaddr* addr, int addrlen);
	// 向服务端/客户端发送数据/函数
	SOCKET mysend(SOCKET sock, const char * buf, int len, int flag, int overtime);
	// 接收从客户端/服务器端发来的数据/命令函数
	int myrecv(SOCKET sock, char * buf,int len, int flag, int overtime, char* EndMark,bool soonflag = FALSE);

private:
	SOCKET m_Socket; // 私有套接字成员变量

};

#endif // !defined(AFX_MYTCPTRAN_H__E7F587CC_B65A_45A7_B926_E5F300620311__INCLUDED_)
