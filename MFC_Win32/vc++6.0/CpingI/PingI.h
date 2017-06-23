// PingI.h: interface for the CPingI class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PINGI_H__4CD64B39_5D24_4320_A5D6_CC9156D2F886__INCLUDED_)
#define AFX_PINGI_H__4CD64B39_5D24_4320_A5D6_CC9156D2F886__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
typedef unsigned long IPAddr; // An IP address

// 定义 IP_OPTION_INFORMATION 结构
typedef struct tagIP_OPTION_INFORMATION
{
	unsigned char Tt1; // Time To Live
	unsigned char Tos; // Type Of Service
	unsigned char Flags; // IP header flags
	unsigned char OptionsSize; // Size in bytes of options data
	unsigned char FAR * OptionsData; // Pointer to options data
} IP_OPTION_INFORMATION;

// 定义 ICMP_ECHO_REPLY 结构
typedef struct tagICMP_ECHO_REPLY
{
	IPAddr Address; // Replying address
	unsigned long Status; // Reply IP_STATUS
	unsigned long RoundTripTime; // RTT in milliseconda
	unsigned short DataSize; // Reply data size in bytes
	unsigned short Reserved; // Recerved for system use
	void FAR *Data; // Pointer to the reply data
	IP_OPTION_INFORMATION Options; // Reply options
} ICMP_ECHO_REPLY;

// 该处使用 typedef 定义 IP_OPTION_INFORMATION和ICMP_ECHO_REPLY结构的别名
typedef IP_OPTION_INFORMATION FAR* LPIP_OPTION_INFRMATION;
typedef ICMP_ECHO_REPLY FAR* LPICMP_ECHO_REPLY;
// 由于下面要用到的3个函数（就是前面介绍的IcmpCreateFile(),IcmpSendEcho(),IcmpSendEcho(),IcmpCloseHandle()）
// 都是在 icmp.dll中的函数，所以声明一个与动态库中类型一致的指针函数变量
typedef HANDLE (WINAPI IcmpCloseHandle) (VIOD);
// 定义上面声明的指针函数变量的别名，用于指向动态链接库中同类型函数的地址
// 后面几条语句的作用同上面两条是一样的
typedef IcmpCreateFile* IpIcmpCreateFile;
typedef BOOL (WINAPI IcmpCloseHandle) (HANDLE　IcmpHandle);
typedef IcmpCloseHandle* IpIcmpCloseHandle;
typedef DWORD (WINAPI IcmpSendEcho)(
				    HANDLE IcmpHandle,
				    IPAddr DestinationAddress,
				    LPVOID RequestData,
				    WORD RequestSize,
				    LPIP_OPTION_INFORMATION RequestOtions,
				    LPVIOD ReplyBuffer,
				    DWORD ReplySize,
				    DWORD TimeSize,
				    DWORD Timeout
				    );
typedef IcmpSendEcho* lpIcmpSendEcho;
// 定义CPingReply结构
struct CPingReply
{
	in_addr address; // The IP address of the replier
	unsigned long RTT; // Round Trip time in Milliseconds
};

// 定义CPingI类
class CPingI  
{
public:
	HINSTANCE icmphandle;
	int Ping( UINT nRetries, LPCSTR pstrHost, HWND hWnd);
	lpIcmpCreateFile sm_pIcmpCreateFile;
	lpIcmpSendEcho sm_pIcmpSendEcho;
	lpIcmpCloseHandle sm_pIcmpCloseHandle;

	CPingI();
	virtual ~CPingI();

};

#endif // !defined(AFX_PINGI_H__4CD64B39_5D24_4320_A5D6_CC9156D2F886__INCLUDED_)
