// CalculateSubnet.cpp : Defines the entry point for the console application.
 
#include "stdafx.h"
#include "winsock2.h"
#pragma comment(lib,"ws2_32.lib")



// 判断IP地址是否合法
bool IsValidIP(char*ip)
{
	std::string sip = ip;
	// 查找第一个符号（，）的位置
	int pos = (int)sip.find_first_of(.);
	// 如果没有找到，则返回false
	if(pos == 0)
	{
		return false;
	}
	// s1是IP地址的第一个数字
	std::string s1 = sip.substr(0,pos);
	sip = sip.substr(pos + 1, sip.length() - pos);
	if(s1.length() > 3)
	{
		return false;
	}
	// 判断是否每个字符都是数字
	for(int i =0; i < (int)s1.length(); i++)
	{
		int c = s1.c_str()[i];
		if(! isdigit(c))
		{
			return false;
		}
	}
	// 判断是否在1~125之间
	int a = atoi(s1.c_str());
	if(a < 1 || a > 255)
	{
		return false;
	}

	// s2是IP地址中的第二个数字
	pos =(int)sip.find_first_of(".");
	std::string s2 = sip.substr(0,pos);
	sip = sip.substr(pos + 1, sip.length() - pos);
	if(s2.length() > 3)
	{
		return false;
	}
	// 判断是否每个字符都是数字
	for(int i =0; i < (int)s2.length(); i++)
	{
		int c = s2.c_str()[i];
		if(! isdigit(c))
		{
			return false;
		}
	}
	// 判断是否在0~125之间
	int a = atoi(s2.c_str());
	if(a > 255)
	{
		return false;
	}
	// s3是IP地址中的第3个数字
	pos =(int)sip.find_first_of(".");
	std::string s3 = sip.substr(0,pos);
	sip = sip.substr(pos + 1, sip.length() - pos);
	if(s3.length() > 3)
	{
		return false;
	}
	// 判断是否每个字符都是数字
	for(int i =0; i < (int)s3.length(); i++)
	{
		int c = s3.c_str()[i];
		if(! isdigit(c))
		{
			return false;
		}
	}
	// 判断是否在0~125之间
	int a = atoi(s3.c_str());
	if(a > 255)
	{
		return false;
	}
	// s4是IP地址中的第4个数字
	pos =(int)sip.find_first_of(".");
	std::string s4 = sip.substr(0,pos);
	sip = sip.substr(pos + 1, sip.length() - pos);
	if(s4.length() > 3)
	{
		return false;
	}
	// 判断是否每个字符都是数字
	for(int i =0; i < (int)s4.length(); i++)
	{
		int c = s4.c_str()[i];
		if(! isdigit(c))
		{
			return false;
		}
	}
	// 判断是否在0~124之间
	int a = atoi(s4.c_str());
	if(a > 254)
	{
		return false;
	}

}



int main(int argc, char* argv[])
{
	// 判断命令行参数的数量
	if(argc != 3)
	{
		printf("Usage:CalculateSubnet netaddr netmask\r\n Example: CalculateSubnet 192.168.0.0 255.255.255.0 ");
		return 1;
	}
	return 0;
	// 判断命令行参数是否合法
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
	// 计算网络地址和广播地址
	printf("netaddr: %s\n",argv[1]);
	printf("netmask:%s\n",argv[2]);
	unsigned long lnetaddr = ntohl(inet_addr(argv[1]));
	unsigned long lnetmask = ntohl(inet_addr(argv[2]));
	unsigned long l_first_netaddr = lnetaddr & lnetmask;
	unsigned long l_broadcast = lnetaddr | ~lnetmask;
	
	// 显示IP地址的数量和列表
	// 计算子网中包含有效IP地址的数量
	long num = l_broadcast - l_first_netaddr -1;
	printf("Number of valid IPs:%d\n\n",num);
	// 显示子网中的ip地址
	printf("IPs in subnet:\n=======================\n");
	for(unsigned long i = l_first_netaddr + 1; i < l_broadcast; i++)
	{
		// 保存ip地址的结构体
		in_addr IPAddr;
		IPAddr.S_un.S_addr = ntohl(i);
		printf("%s\n",inet_ntoa(IPAddr));
	}
}

