// client.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<winsock2.h>
#include<stdio.h>
#include<windows.h>
#pragma comment(lib,"WS2_32.lib")

#define BUF_SIZE 256



int main(int argc, char* argv[])
{

	// 初始化WS2_32.dll
	WSADATA wsaData;
	WORD sockVersion = MAKEWORD(2,0);
	::WSAStartup(sockVersion,&wsaData);
	// 创建TCP Socket
	SOCKET s = ::socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(s == INVALID_SOCKET)
	{
		printf("Failed socket() \n");
		::WSACleanup();
		return 0;
	}
	 // 端口
	int port;
	char addr[15];
	printf("    请输入远程主机ip:");
	scanf("%s",&addr);
	printf("请输入远程主机端口号:");
	scanf("%d",&port);

	sockaddr_in servAddr;
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(port);
	servAddr.sin_addr.S_un.S_addr = inet_addr(addr);
	if(::connect(s,(sockaddr*)&servAddr,sizeof(servAddr)) == -1)
	{
		printf("Failed connect() \n");
		::WSACleanup();
		return 0;
	}
	printf("------================连接成功=============--\r\n");
	printf("---Sever: %s : %d========--\r\n",addr,port);

	char buf[BUF_SIZE]; // 接收数据
	while(true)
	{
		ZeroMemory(buf,BUF_SIZE);
		// 向服务器发送数据
		printf("请输入要发送的消息：");
		//char str[BUF_SIZE];
		// 接受输入的数据
		scanf("%s",&buf);
		
		// 向服务器发送数据
		int nRecv = ::send(s,buf,strlen(buf),0);
		if(SOCKET_ERROR == nRecv)
		{
			printf("send failed! \n");
			closesocket(s);
			WSACleanup();
			return -1;
		}
		// 接收服务器回传的数据
		nRecv = ::recv(s,buf,sizeof(buf)+1,0);
		printf("Recv From Server: %s \n",buf);
		// 如果收到“quit”则退出
		if(strcmp(buf,"quit") == 0)
		{
			printf("quit! \n");
			break;
		}
	}

	

	// 释放资源
	::closesocket(s);
	::WSACleanup();
	// 暂停，按任意键继续
	system("pause");
	return 0;
}
