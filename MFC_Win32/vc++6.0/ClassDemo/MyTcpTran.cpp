// MyTcpTran.cpp: implementation of the CMyTcpTran class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MyTcpTran.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
/*
*****************************************************
������CmyTcpTran
���ܣ���ɣԣãе�ͨ��
*****************************************************
*/
       // ���캯��
CMyTcpTran::CMyTcpTran()
{
	// �׽��ַ��� INVALID_SOCKET,����Ϊ���׽�����Ч�������ڹ��캯����Ϊ��Ա����Ĭ�ϸ�ֵΪ��Ч���׽��֣��𵽳�ʼ�������á�
	m_Socket = INVALID_SOCKET;

}
           // ��������
CMyTcpTran::~CMyTcpTran()
{
	//

}

/*
	��������InitSocketLibary
	���ܣ�  ��ʼ��SOCKET��ͨ�ſ⣬Ҫ��winsocket 2
	������  lowver:�汾�ĵ�λ
	        higver:�汾�ĸ�λ
	����ֵ��TRUE��ʾ�ɹ���FALSE����ʾʧ��
*/
bool CMyTcpTran::InitSocketLibray(int lowver, int higver)
{
	WORD wVersion = 0;
	int errret = -1;
	WSADATA wsaData;

	// MAKEWORD ������byte�ͺϲ���һ��word�ͣ�������һ���ǰ汾�ĵ�8λ��һ���ǰ汾�ĸ�8λ
	// ��λ�ֽ�ָ�����汾����λ�ֽ�ָ�����汾�����һ����ʹ��2.1�汾��socket,��������£�
	// wVersion = MAKEWORD(2.1);
	wVersion = MAKEWORD(lowver,higver);
	// ���غͳ�ʼ��socket��Ӧ�Ķ�̬���ӿ�ws2_32.dll��һЩ��Ϣ��Ϊʹ��socket������
	errret = WSAStartup(wVersion,&wsaData);

	// �ж�socket��Ӧ�Ķ�̬���ӿ�İ汾
	if( LOBYTE( wsaData.wVersion) != 2 ||
		HIBYTE( wsaData.wVersion) != 2 )
	{
		MessageBox(NULL,"winsocket��汾��"��"��ʾ"��MB_OK);
		return FALSE;
	}
	return TRUE;
}
/*
	��������InitSocket
	���ܣ�  �������ͳ�ʼ��SOCKET��Դ
	������  SocketType:SOCK_BIND ��ʾԤ�����ض˿�
			   SOCK_NOBIND ��ʾ��Ԥ��
		BindIp:ҪԤ����IP��ַ��������Ϊ���������ַ�����ʮ���Ʊ�ʾIP��ַ
		BindPort:ҪԤ���ı��ض˿ڣ����Ϊ�㣬��ʾϵͳ�Զ�����
		opt:�����Ƿ�֧�ֶ˿ڸ���
	����ֵ������INVALID_SOCKET
		��ȷ�����ؿ��õ�SOCKET
*/
SOCKET CMyTcpTran::InitSocket( int SocketType, string strBindIp, u_short BindPort, int opt)
{
	SOCKET socketid = INVALID_SOCKET;
	// ����һ���ܹ���������ͨ�ŵ��׽���
	socketid = socket( PF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN sockStruct;
	// ʹ��TCP/IPЭ��
	sockStruct.sin_family = AF_INET;
	if( strBindIp.empty())
	{
		// ����strBindIpΪ�գ�����INADDR_ANY��ʾSOCKET���Խ��������κ�IP����Ϣ
		sockStruct.sin_addr.S_un.S_addr = INADDR_ANY;
	}
	else
	{
		// ����strBind��Ϊ�գ���strBindIpת��Ϊchar*��
		// ��IP��ַ�ӵ�����ʽת��Ϊ�޷��ų�������
		sockStruct.sin_addr.S_un.S_addr = inet_addr(strBindIp.c_str());
	}

	// ������BindPortת��Ϊ�����ֽ���󱣴�
	sockStruct.sin_port = htons(BindPort);
	// ���󶨶˿�
	if( socketType == SOCK_NOBIND)
	{
		// ��sockStruct�ṹ��ָ���������ϵļ������������
		if( connect( socketid, (LPSOCKETADDR)&sockStruct, sizeof(sockStruct)) == SOCKET_ERROR)
		{
			// �������ϵļ��������ʧ��
			// Output DebugString("���Ӵ���");
			closesocket(socketid);
			// �ر��Ѿ��򿪵��׽��֣���ֹռ���ڴ�
			shutdown(socketid,2);
			// �����׽�����Ч
			socketid = INVALID_SOCKET;
		}
		m_Socket = socketid;
	}
	// ����ǰ󶨱��ض˿�
	else if( SocketType == SOCK_BIND)
	{
		// ����sockStructָ������������IP�Ͷ˿�
		if(bind(socketid,(sockaddr*)&sockStruct,sizeof(sockaddr_in)) == SOCKET_ERROR)
		{
			// �󶨶˿�ʧ��
			closesocket(socketid);
			// �����׽�����Ч
			socketid = INVALID_SOCKET;
		}
		else
		{
			// ��IP�Ͷ˿ڳɹ�����������������������������Ӷ���
			// SOMAXCONNָ������������
			if( listen(socketid,SOMAXCONN) == SOCKET_ERROR)
			{
				// ������������ʧ�ܣ���ر��׽��֣��������׽�����Ч״̬
				closesocket(socketid);
				socketid = INVALID_SOCKET;
			}
		}
		m_Socket = socketid;
	}
	return socketid;
}

/*
	��������myaccept��
	���ܣ�  ����һ���µ��׽��������addrָ���Ŀͻ����׽��ֽ�������ͨ��
	������  s:���ڼ���״̬�����׽���
		addr:�´������׽��ֵĵ�ַ�ṹ
		addrlen���´������׽��ֵĵ�ַ�ṹ�ĳ���
	����ֵ������ʧ�ܷ��أ�INVALID_SOCKET
		���óɹ����أ����õ�SOCKET
*/
SOCKET CMyTcpTran::myaccept( SOCKET s, struct sockaddr* addr, int* addrlen)
{
	// �����µ��׽��ֲ���ʼ��ΪINVALID_SOCKET
	SOCKET accpsocket = INVALID_SOCKET;
	// accept���óɹ����ؿ��õ��׽��֣�����ʧ��ͬ������INVALID_SOCKET
	accpsocket = accept(s, addr, addrlen);
	return accpsocket;
}

/*
	��������myrecv
	���ܣ��������ͳ�ʼ��SOCKET��Դ
	������sock:���ն��׽���������
		buf:������Ž��յ������ݵĻ�����
		len�����ܵ������ݵĴ�С
		flag��һ������Ϊ0
		overtime����ʱʱ��
		EndMark���������
		Soonflag���Ƿ���������
	����ֵ�����յ����ݵ��ֽ���
*/
int CMyTcpTran::myrecv(SOCKET sock, char* buf, int len, int flag, int overtime, char* EndMark, bool soonflag)
{
	// �������
	int ret;
	int nLeft = len;
	int idx = 0;
	int nCount = 0;
	fd_set readfds; // fd_set���ļ��������ļ���
	struct timeval timeout;
	timeout.tv_sec = 0;// ���ó�ʱֵ
	timeout.tv_usec = 500;
	DWORD s_time = GetTickCount(); // ���شӲ���ϵͳ���������ھ����ĺ�����

	while( nLeft > 0)
	{
		// ������Ϣ
		MSG msg;
		PeekMessage( &msg,NULL, 0, 0, PM_REMOVE);
		// ���յ�����Ϣ���˳���Ϣ
		if( msg.message == WM_QUIT)
		{
			return 0;
		}
		FD_ZERO( &readfds); // ��set����
		FD_SET( sock, &readfds); // ��fd����set
		// select����ʽ���������׽���IO�ģ���������޹�����
		if( select( 0, &readfds, NULL, NULL, %timeout ) == SOCKET_ERROR)
		{
			return SOCKET_ERROR;
		}
		DWORD e_time = GetTickCount();
		if( !FD_ISSET( sock, &readfds))
		{
			if( e_time - s_time > overtime*1000 ) // ��ʱ
			{
				return SOCKET_TIMEOUT;
			}
			else
			{
				continue;
			}
		}
		ret = recv( sock, &buf[idx], nleft, flag ); // ��������

		if( soonflag == TRUE)
		{
			// �������ؽ��յ����ֽ���
			return ret;
		}
		s_time = e_time; // ֻҪ�����ݾ������ó�ʼֵ

		if( ret <= 0 )
		{
			// ������
			int LastError = GetLastError();
			if( ( -1 == ret) && ( WSAETIMEDOUT == LastError ) )
			{
				continue;
			}
			if( (-1 == ret ) && ( WSAEWOULDBLOCK == LastError ) )
			{
				if( nCount < 2000 )
				{
					Sleep( 10 );
					nCount++;
					continue;
				}
			}
			return ret;
		}
		nCount = 0;

		nLeft -= ret;
		idx += ret;
		if(EndMark != NULL && idx > 5)
		{
			if( strstr( buf + ( idx - 5 ), EndMark ) != NULL )
			{
				break;
			}
		}
	}
	return idx;
}


/*
	��������mysend
	���ܣ�  ��ָ����SOCKET��������
	������  socket�����Ͷ��׽���������
		buf:�������Ҫ�������ݵĻ�����
		flag:һ����0
		overtime:�������ó�ʱʱ��
	����ֵ��ʵ�ʷ������ݵ��ֽ���
*/
int CMyTcpTran::mysend( SOCKET sock, const char *buf, int len, int flag, int overtime )
{
	// �������
	int ret;
	int nLeft = len;
	int idx = 0;
	fd_set readfds;
	struct timeval timeout;
	timeout.tv_sec = 0;
	timeout.tv_usec = 500;
	DWORD s_time = GetTickCount();
	while ( nLeft > 0 )
	{
		// ��Ի����͹ر���Ϣ
		MSG msg;
		PeekMessage( &msg, NULL, 0, 0, PM_REMOVE );
		if( msg.message == WM_QUIT )
		{
			return 0;
		}
		FD_ZERO( &readfds );
		FD_SET( sock, &readfds );
		int errorret = select( 0, NULL, &readfds, NULL, &timeout );
		if( errorret == SOCKET_ERROR )
		{
			OutputDebugString("mysendEx SOCKET������");
			return SOCKET_ERROR;
		}
		// ���㵱ǰʱ��
		DWORD e_time = GetTickCount();
		if ( !FD_ISSET( sock, &readfds ) )
		{
			// �����ʱ������
			if( e_time - s_time > overtime*1000 )
			{
				OutputDebugString("mysendEx �������ݳ�ʱ");
				return 0;
			}
			else
			{
				// OutputDebugString("��������FD_ISSET��ʱ");
				continue;
			}
		}
		ret = send( sock, &buf[idx], nLeft, flag );
		if( ret <= 0 )
		{
			return ret;
		}
		nLeft -= ret;
		idx += ret;
	}
	return len;
}
