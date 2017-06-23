// PingI.cpp: implementation of the CPingI class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PingI.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#define MIN_ICMP_PACKET_SIZE 8 // 最小8个自己的ICMP包头
#define MAX_ICMP_PACKET_SIZE 1024 // ICMP包最大值
CPingI::CPingI()
{
	// 构造函数
	// 加载icmp.dll库
	sm_pIcmpSendEcho = NULL;
	sm_pIcmpCreateHile = NULL;
	sm_pIcmpCloseHandle = NULL;
	// 将Dll加载到当前的应用程序中并返回当前Dll文件的句柄
	// 在编译程序之前，首先要将ICMP.dll文件拷贝到工程所在的目录或Windows系统目录下
	// 否则编译会有错误
	icmphandle = loadlibrary("ICMP.Dll");
	if( icmphandle == NULL)
	{
		// TRACE( _T("Could not load up the ICMP DLL\n") );
		return;
	}
	// 得到IcmpCreateFile,IcmpSendEcho,IcmpCloseHandle函数地址
	sm_pIcmpCraeateFile = (lpIcmpCtrateFlie) GetProcAddress(icmphandle,"IcmpCreateFile");
	sm_pIcmpSendEcho = (lpIcmpSendEcho) GetProcAddress(icmphandle,"IcmpSendEcho");
	sm_pIcmpCloseHandle = (lpIcmpCloseHandle) GetProcAddress(icmphandle,"IcmpCloseHandle");

	if( sm_pIcmpCreateFile == NULL || sm_pIcmpSendEcho == NULL || sm_pIcmpCloseHandle == NULL )
	{
		// 得到的IcmpCreateFile,IcmpSendEcho,IcmpCloseHandle 3个函数细致，如果有一个为NULL
		// 使用OutputDebugString输出调试信息，输出的结果可以在vs集成环境中看到也可以使用
		// 工具dbgView.exe捕捉结果，便于很快在debug的时候找到错误的原因。
		OutputDebugString("Could not find ICMP functions in ths ICMP DLL\n");
	}
}

CPingI::~CPingI()
{
	// 动态链接库中的函数使用完毕后要用FreeLibrary卸载该动态链接库
	if( icmphandle )
	{
		FreeLibrary(icmphandle);
		icmphandle = NULL;

	}
}


/*
	函数名：Ping
	功能：	向目标主机发送ping请求，根据返回的信息判断目标主机在网络中是否存活
	参数：	nRetries:超时时间，以秒为单位
		pstrHost：点间隔格式的IP地址
		nWnd：调用该ping方法的窗口句柄
	返回值：网络中主机存活返回TRUE，否则返回FALSE
*/
int CPingI::Ping( UINT nRetries, LPCSTR pstrHost, HWND hWnd )
{
	// 如果在构造函数执行后没有得到动态链接库中函数地址，或得到不正确的地址，程序返回0
	if( sm_pIcmpSendEcho == NULL )
	{
		return 0;
	}
	DWORD dwTimeout = 1000; // 超时时间
	UCHAR nPacketSize = 32; // 数据包的大小
	// 将点间隔格式的IP地址转换为一个数字的Internet地址
	unsigned long addr = inet_addr(pstrHost);
	// 将字符串pstrHost表示的网络地址（如192.168.0.1）转化成32位的网络字节序二进制值
	// 若成功，返回32位二进制的网络字节序地址，若出错，返回INADDR_NONE
	if( addr == INADDR_NONE )
	{
		// 如果点形式的IP地址转换出错，则解析其IP地址
		// 返回一个指向hostent结构的指针，否则，返回一个空指针
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
	// 创建ICMP句柄
	HANDLE hIP = sm_pIcmpCreateFile();
	if( hIP == INVALID_HANDLE_VALUE )
	{
		// 调用IcmpCreateFile失败
		// TRACE(_T("Could not get a valid ICMP handle\n"));
		return FALSE;
	}
	// 填充结构选项
	IP_OPTION_INFORMATION OptionInfo;
	ZeroMemory( &OptionInfo, sizeof(IP_OPTION_INFORMATION) );
	OptionInfo.Tt1 = 128;

	//填充要发送的数据
	unsigned char pBuf[36];
	memset( pBuf, 'E',nPacketSize);

	// DO the actual Ping
	int nReplySize = sizeof( ICMP_ECHO_REPLY ) + max( MIN_ICMP_PACKET_SIZE, nPacketSize );
	unsigned char pReply[100];
	ICMP_ECHO_REPLY* pEchoReply = (ICMP_ECHO_REPLY*)pReply;
	DWORD nRecvPackets = sm_pIcmpSendEcho( hIP, addr, pBuf, nPacketSize, &OptionInfo, pReply, nReplySize, dwTimeout );
	// 检测是否会有包
	BOOL bSuccess = ( nRecvPackets == 1 );
	// Check the IP status is OK (O is IP Success)
	if(bSuccess && ( pEchoReply->Status != 0 ) )
	{
		bSuccess = FALSE;
		SetLastError( pEchoReply->Status );
	}
	// 关闭ICMP句柄
	sm_pIcmpCloseHandle(hIP);
	return bSeccess;
}
