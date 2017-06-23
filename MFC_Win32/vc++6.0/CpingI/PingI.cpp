// PingI.cpp: implementation of the CPingI class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PingI.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#define MIN_ICMP_PACKET_SIZE 8 // ��С8���Լ���ICMP��ͷ
#define MAX_ICMP_PACKET_SIZE 1024 // ICMP�����ֵ
CPingI::CPingI()
{
	// ���캯��
	// ����icmp.dll��
	sm_pIcmpSendEcho = NULL;
	sm_pIcmpCreateHile = NULL;
	sm_pIcmpCloseHandle = NULL;
	// ��Dll���ص���ǰ��Ӧ�ó����в����ص�ǰDll�ļ��ľ��
	// �ڱ������֮ǰ������Ҫ��ICMP.dll�ļ��������������ڵ�Ŀ¼��WindowsϵͳĿ¼��
	// ���������д���
	icmphandle = loadlibrary("ICMP.Dll");
	if( icmphandle == NULL)
	{
		// TRACE( _T("Could not load up the ICMP DLL\n") );
		return;
	}
	// �õ�IcmpCreateFile,IcmpSendEcho,IcmpCloseHandle������ַ
	sm_pIcmpCraeateFile = (lpIcmpCtrateFlie) GetProcAddress(icmphandle,"IcmpCreateFile");
	sm_pIcmpSendEcho = (lpIcmpSendEcho) GetProcAddress(icmphandle,"IcmpSendEcho");
	sm_pIcmpCloseHandle = (lpIcmpCloseHandle) GetProcAddress(icmphandle,"IcmpCloseHandle");

	if( sm_pIcmpCreateFile == NULL || sm_pIcmpSendEcho == NULL || sm_pIcmpCloseHandle == NULL )
	{
		// �õ���IcmpCreateFile,IcmpSendEcho,IcmpCloseHandle 3������ϸ�£������һ��ΪNULL
		// ʹ��OutputDebugString���������Ϣ������Ľ��������vs���ɻ����п���Ҳ����ʹ��
		// ����dbgView.exe��׽��������ںܿ���debug��ʱ���ҵ������ԭ��
		OutputDebugString("Could not find ICMP functions in ths ICMP DLL\n");
	}
}

CPingI::~CPingI()
{
	// ��̬���ӿ��еĺ���ʹ����Ϻ�Ҫ��FreeLibraryж�ظö�̬���ӿ�
	if( icmphandle )
	{
		FreeLibrary(icmphandle);
		icmphandle = NULL;

	}
}


/*
	��������Ping
	���ܣ�	��Ŀ����������ping���󣬸��ݷ��ص���Ϣ�ж�Ŀ���������������Ƿ���
	������	nRetries:��ʱʱ�䣬����Ϊ��λ
		pstrHost��������ʽ��IP��ַ
		nWnd�����ø�ping�����Ĵ��ھ��
	����ֵ����������������TRUE�����򷵻�FALSE
*/
int CPingI::Ping( UINT nRetries, LPCSTR pstrHost, HWND hWnd )
{
	// ����ڹ��캯��ִ�к�û�еõ���̬���ӿ��к�����ַ����õ�����ȷ�ĵ�ַ�����򷵻�0
	if( sm_pIcmpSendEcho == NULL )
	{
		return 0;
	}
	DWORD dwTimeout = 1000; // ��ʱʱ��
	UCHAR nPacketSize = 32; // ���ݰ��Ĵ�С
	// ��������ʽ��IP��ַת��Ϊһ�����ֵ�Internet��ַ
	unsigned long addr = inet_addr(pstrHost);
	// ���ַ���pstrHost��ʾ�������ַ����192.168.0.1��ת����32λ�������ֽ��������ֵ
	// ���ɹ�������32λ�����Ƶ������ֽ����ַ������������INADDR_NONE
	if( addr == INADDR_NONE )
	{
		// �������ʽ��IP��ַת�������������IP��ַ
		// ����һ��ָ��hostent�ṹ��ָ�룬���򣬷���һ����ָ��
		hostent* hp = gethostbyname(pstrHost);
		if(hp)
		{
			memcpy( &addr, hp->h_addr, hp->h_length);
		}
		else
		{
			// TRACE(_T("Could not resolve the host name %s\n"),pstrHost);
			return FALSE;
		}
	}
	// ����ICMP���
	HANDLE hIP = sm_pIcmpCreateFile();
	if( hIP == INVALID_HANDLE_VALUE )
	{
		// ����IcmpCreateFileʧ��
		// TRACE(_T("Could not get a valid ICMP handle\n"));
		return FALSE;
	}
	// ���ṹѡ��
	IP_OPTION_INFORMATION OptionInfo;
	ZeroMemory( &OptionInfo, sizeof(IP_OPTION_INFORMATION) );
	OptionInfo.Tt1 = 128;

	//���Ҫ���͵�����
	unsigned char pBuf[36];
	memset( pBuf, 'E',nPacketSize);

	// DO the actual Ping
	int nReplySize = sizeof( ICMP_ECHO_REPLY ) + max( MIN_ICMP_PACKET_SIZE, nPacketSize );
	unsigned char pReply[100];
	ICMP_ECHO_REPLY* pEchoReply = (ICMP_ECHO_REPLY*)pReply;
	DWORD nRecvPackets = sm_pIcmpSendEcho( hIP, addr, pBuf, nPacketSize, &OptionInfo, pReply, nReplySize, dwTimeout );
	// ����Ƿ���а�
	BOOL bSuccess = ( nRecvPackets == 1 );
	// Check the IP status is OK (O is IP Success)
	if(bSuccess && ( pEchoReply->Status != 0 ) )
	{
		bSuccess = FALSE;
		SetLastError( pEchoReply->Status );
	}
	// �ر�ICMP���
	sm_pIcmpCloseHandle(hIP);
	return bSeccess;
}
