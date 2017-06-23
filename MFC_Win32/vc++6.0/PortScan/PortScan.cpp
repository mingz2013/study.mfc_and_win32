// PortScan.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include<winsock.h>

#pragma comment(lib, "ws2_32")
// 加载必须的头文件和库文件
void usage(char *prog)
{
	printf("Usage:GSGBannerScan.exe 127.0.0.1 1 65535\n");
	printf("GSGBannerScan.exe IP Strtport Endport\n");
}
// 自定义帮主函数
int main(int argc, char* argv[])
{
	if(argc != 4)
	{
		usage( argv[0] );
		return -1;
	}// 如果参数不是4个，显示帮助
	WSADATA wsa;
	if ( WSAStartup( MAKEWORD(2,2), &wsa ) != 0 )
	{
		printf("Winsock Dll init Failed! \n");
		return -1;
	}// 初始化Socket版本
	int nowport, count;
	// 定义当前端口和计数器
	struct sockaddr_in sa;
	int startport = atoi(argv[2]);
	int endport = atoi(argv[3]);
	// 设置开始端口和结束端口
	if( endport < startport )
	{
		printf("don&#39;t doing,endport < startport\n");
		return -1;
	}
	// 判断端口的有效性
	nowport = startport;
	// 设置当前端口 = 开始端口
	printf("Start scan.......\n");
	for( nowport; nowport < endport; nowport++)
	{
		printf("Scanning port--------- %d----------\n",nowport);
		sa.sin_family = AF_INET;
		sa.sin_addr.S_un.S_addr = inet_addr(argv[1]);
		sa.sin_port = htons(nowport);
		// 设置目标主机
		SOCKET sockFD = socket( AF_INET, SOCK_STREAM, 0);
		if( sockFD == INVALID_SOCKET )
		{
			printf("Socket create Error!\n");
			return -1;
		}// 建立socket套接字
		int iTimeOut = 5000;// 设置超时
		setsockopt( sockFD, SOL_SOCKET, SO_RCVTIMEO, (char*)&iTimeOut,sizeof(iTimeOut));
		if( connect( sockFD, (const sockaddr*)&sa, sizeof(sa) ) == SOCKET_ERROR )
		{
			closesocket(sockFD);
		}// 如果连接错误
		else
		{
			count = count + 1; // 连接成功，计数器加1
			printf("%s Find %d Port is Opend!\n",argv[1],nowport);
			if( nowport == 21 )
			{
				char buff[2048] = {0};
				char hello[5] = {"test"};
				send( sockFD, hello, sizeof(hello), 0 );
				recv( sockFD, buff, sizeof(buff), 0 );
				printf("FTP Banner: %s\n",buff);
				// 这里可以加入send(sockFD,"ftp",3,0)
				// ....来判断ftp是否可以匿名登录和写权限，等等
				/*
				{
				send(client,"ftp",3,0);
				......通过发送用户名和密码，然后接收返回判断是否可以登录
				}
				*/
				// 这些代码可以由读者来完成
			}// 如果是21端口，显示端口banner
			else
			{
				if( nowport == 80 )
				{
					char buff[2048] = {0};
					char get[30] = {"GET HTTP 1.0/1.1\n\n\r\r\r"};
					send( sockFD, get, sizeof(get), 0 );
					recv( sockFD, buff, sizeof(buff), 0);
					printf("The server is %s\n",buff);
				}// 如果是80端口，显示bannner
				//else if (nowport == %d xx)
				// 这里可以加入更多的banner判断
				// 这些代码可以由读者来完成
				closesocket(sockFD);
			}
		}

	}
	printf("Scan End......\nFind %d Port is Opend!\n",count); // 在这里可以把结果写到一个文本文档里
	// 显示结束
	WSACleanup();
	// 释放socket资源
	return 0;
}
