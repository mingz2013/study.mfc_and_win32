// MyTcpTran.h: interface for the CMyTcpTran class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYTCPTRAN_H__E7F587CC_B65A_45A7_B926_E5F300620311__INCLUDED_)
#define AFX_MYTCPTRAN_H__E7F587CC_B65A_45A7_B926_E5F300620311__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define SOCKETBIND 1   // ��ʾ�������˼����˿ڵȴ�����
#define SOCKETNOBIND 2 // ��ʾ���������������ӿͻ���
#define SOCKET_TIMEOUT -100 // �׽��ֳ�ʱ
#include"winsock2.h"
#include<string>
using namespace std;
#pragma comment (lib,"ws2_32.lib")

socket m_socket; // m�������е�

class CMyTcpTran  
{
public:
	CMyTcpTran(); // ���캯��
	virtual ~CMyTcpTran(); // ��������
public:
	static bool InitSocketLibray(int lowver,int higver); // ��ʼ��Winsock API ���ӿ��ļ�

public:
	// ��ʼ��socket����
	SOCKET InitSocket( int SocketType, string strBindIp, u_short BindPort, int opt );
	// ��Ա��ؼ����Ĵ�����
	SOCKET myaccept(SOCKET s, struct sockaddr* addr, int addrlen);
	// ������/�ͻ��˷�������/����
	SOCKET mysend(SOCKET sock, const char * buf, int len, int flag, int overtime);
	// ���մӿͻ���/�������˷���������/�����
	int myrecv(SOCKET sock, char * buf,int len, int flag, int overtime, char* EndMark,bool soonflag = FALSE);

private:
	SOCKET m_Socket; // ˽���׽��ֳ�Ա����

};

#endif // !defined(AFX_MYTCPTRAN_H__E7F587CC_B65A_45A7_B926_E5F300620311__INCLUDED_)
