// PingI.h: interface for the CPingI class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PINGI_H__4CD64B39_5D24_4320_A5D6_CC9156D2F886__INCLUDED_)
#define AFX_PINGI_H__4CD64B39_5D24_4320_A5D6_CC9156D2F886__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
typedef unsigned long IPAddr; // An IP address

// ���� IP_OPTION_INFORMATION �ṹ
typedef struct tagIP_OPTION_INFORMATION
{
	unsigned char Tt1; // Time To Live
	unsigned char Tos; // Type Of Service
	unsigned char Flags; // IP header flags
	unsigned char OptionsSize; // Size in bytes of options data
	unsigned char FAR * OptionsData; // Pointer to options data
} IP_OPTION_INFORMATION;

// ���� ICMP_ECHO_REPLY �ṹ
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

// �ô�ʹ�� typedef ���� IP_OPTION_INFORMATION��ICMP_ECHO_REPLY�ṹ�ı���
typedef IP_OPTION_INFORMATION FAR* LPIP_OPTION_INFRMATION;
typedef ICMP_ECHO_REPLY FAR* LPICMP_ECHO_REPLY;
// ��������Ҫ�õ���3������������ǰ����ܵ�IcmpCreateFile(),IcmpSendEcho(),IcmpSendEcho(),IcmpCloseHandle()��
// ������ icmp.dll�еĺ�������������һ���붯̬��������һ�µ�ָ�뺯������
typedef HANDLE (WINAPI IcmpCloseHandle) (VIOD);
// ��������������ָ�뺯�������ı���������ָ��̬���ӿ���ͬ���ͺ����ĵ�ַ
// ���漸����������ͬ����������һ����
typedef IcmpCreateFile* IpIcmpCreateFile;
typedef BOOL (WINAPI IcmpCloseHandle) (HANDLE��IcmpHandle);
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
// ����CPingReply�ṹ
struct CPingReply
{
	in_addr address; // The IP address of the replier
	unsigned long RTT; // Round Trip time in Milliseconds
};

// ����CPingI��
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
