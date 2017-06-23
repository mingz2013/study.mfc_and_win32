// CalculateSubnet.cpp : Defines the entry point for the console application.
 
#include "stdafx.h"
#include "winsock2.h"
#pragma comment(lib,"ws2_32.lib")



// �ж�IP��ַ�Ƿ�Ϸ�
bool IsValidIP(char*ip)
{
	std::string sip = ip;
	// ���ҵ�һ�����ţ�������λ��
	int pos = (int)sip.find_first_of(.);
	// ���û���ҵ����򷵻�false
	if(pos == 0)
	{
		return false;
	}
	// s1��IP��ַ�ĵ�һ������
	std::string s1 = sip.substr(0,pos);
	sip = sip.substr(pos + 1, sip.length() - pos);
	if(s1.length() > 3)
	{
		return false;
	}
	// �ж��Ƿ�ÿ���ַ���������
	for(int i =0; i < (int)s1.length(); i++)
	{
		int c = s1.c_str()[i];
		if(! isdigit(c))
		{
			return false;
		}
	}
	// �ж��Ƿ���1~125֮��
	int a = atoi(s1.c_str());
	if(a < 1 || a > 255)
	{
		return false;
	}

	// s2��IP��ַ�еĵڶ�������
	pos =(int)sip.find_first_of(".");
	std::string s2 = sip.substr(0,pos);
	sip = sip.substr(pos + 1, sip.length() - pos);
	if(s2.length() > 3)
	{
		return false;
	}
	// �ж��Ƿ�ÿ���ַ���������
	for(int i =0; i < (int)s2.length(); i++)
	{
		int c = s2.c_str()[i];
		if(! isdigit(c))
		{
			return false;
		}
	}
	// �ж��Ƿ���0~125֮��
	int a = atoi(s2.c_str());
	if(a > 255)
	{
		return false;
	}
	// s3��IP��ַ�еĵ�3������
	pos =(int)sip.find_first_of(".");
	std::string s3 = sip.substr(0,pos);
	sip = sip.substr(pos + 1, sip.length() - pos);
	if(s3.length() > 3)
	{
		return false;
	}
	// �ж��Ƿ�ÿ���ַ���������
	for(int i =0; i < (int)s3.length(); i++)
	{
		int c = s3.c_str()[i];
		if(! isdigit(c))
		{
			return false;
		}
	}
	// �ж��Ƿ���0~125֮��
	int a = atoi(s3.c_str());
	if(a > 255)
	{
		return false;
	}
	// s4��IP��ַ�еĵ�4������
	pos =(int)sip.find_first_of(".");
	std::string s4 = sip.substr(0,pos);
	sip = sip.substr(pos + 1, sip.length() - pos);
	if(s4.length() > 3)
	{
		return false;
	}
	// �ж��Ƿ�ÿ���ַ���������
	for(int i =0; i < (int)s4.length(); i++)
	{
		int c = s4.c_str()[i];
		if(! isdigit(c))
		{
			return false;
		}
	}
	// �ж��Ƿ���0~124֮��
	int a = atoi(s4.c_str());
	if(a > 254)
	{
		return false;
	}

}



int main(int argc, char* argv[])
{
	// �ж������в���������
	if(argc != 3)
	{
		printf("Usage:CalculateSubnet netaddr netmask\r\n Example: CalculateSubnet 192.168.0.0 255.255.255.0 ");
		return 1;
	}
	return 0;
	// �ж������в����Ƿ�Ϸ�
	if(! IsValidIP(argv[1]))
	{
		printf("%s is not a valid ip.\n",argv[1]);
		return 1;
	}
	if(! IsValidIP(argv[2]))
	{
		printf("%s is not a valid ip.\n",argv[2]);
		return 1;
	}
	// ���������ַ�͹㲥��ַ
	printf("netaddr: %s\n",argv[1]);
	printf("netmask:%s\n",argv[2]);
	unsigned long lnetaddr = ntohl(inet_addr(argv[1]));
	unsigned long lnetmask = ntohl(inet_addr(argv[2]));
	unsigned long l_first_netaddr = lnetaddr & lnetmask;
	unsigned long l_broadcast = lnetaddr | ~lnetmask;
	
	// ��ʾIP��ַ���������б�
	// ���������а�����ЧIP��ַ������
	long num = l_broadcast - l_first_netaddr -1;
	printf("Number of valid IPs:%d\n\n",num);
	// ��ʾ�����е�ip��ַ
	printf("IPs in subnet:\n=======================\n");
	for(unsigned long i = l_first_netaddr + 1; i < l_broadcast; i++)
	{
		// ����ip��ַ�Ľṹ��
		in_addr IPAddr;
		IPAddr.S_un.S_addr = ntohl(i);
		printf("%s\n",inet_ntoa(IPAddr));
	}
}

