// Server.cpp : Defines the entry point for the console application.
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
	// 填充sockaddr_in 结构
	sockaddr_in sin;
	sin.sin_family = AF_INET;
        // 端口
	int port;
	printf("请输入绑定的本地端口号:");
	scanf("%d",&port);
	sin.sin_port = htons(port);
	sin.sin_addr.S_un.S_addr = INADDR_ANY;
	// 绑定这个套接字到一个本地地址
	if(::bind(s,(LPSOCKADDR)&sin,sizeof(sin)) == SOCKET_ERROR)
	{
		printf("Failed bind() \n");
		::WSACleanup();
		return 0;
	}
	// 切换到监听状态
	if(::listen(s,2) == SOCKET_ERROR)
	{
		printf("Failed listen()");
		::WSACleanup();
		return 0;
	}
	printf("服务端在 %d 端口监听中。。。\n\n",port);
	
	SOCKET client; // 执行accept()后新建的用于世纪通信的套接字
	sockaddr_in remoteAddr; // 用于接收接入地址
        int len = sizeof(remoteAddr);
	char szText[] = " Server\r\n";
	

	while(TRUE)
	{
		// 等待接收接入请求
		client = ::accept(s,(SOCKADDR*)&remoteAddr,&len);
		if(client == INVALID_SOCKET)
		{
			printf("Failed accept()"); // 打印错误编码
			return 0;
		}
		else
		{
			printf("********************* 接到连接： %s : %d **************\r\n",inet_ntoa(remoteAddr.sin_addr),remoteAddr.sin_port); // 打印接入地址
		}
		while(true)
		{
			//printf("------================连接成功=============--\r\n\n");
			
			char buf[BUF_SIZE]; // 接收数据
			ZeroMemory(buf,BUF_SIZE); // 清空接收数据的缓冲区
			int nRecv = ::recv(client,buf,BUF_SIZE,0);
			if(SOCKET_ERROR == nRecv)
			{
				printf("recv failed! \n");
				break;
			}
			//获取当前系统时间
			SYSTEMTIME st;
			GetLocalTime(&st);
			char sDateTime[30];
			if(nRecv > 0)
			{
				buf[nRecv] = '\0';
				printf("%4d-%2d-%2d %2d:%2d:%2d",st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond);
				// 打印输出信息
				printf("Recv From Client [%s:%d] :%s\n",inet_ntoa(remoteAddr.sin_addr),remoteAddr.sin_port,buf);
				// 如果客户端发送“quit”字符串，则服务器退出
				if(strcmp(buf,"quit") == 0)
				{
					nRecv = ::send(client,"quit",strlen("quit"),0);
					break;
				}
				// 否则向客户端发送回显字符串
				else
				{
					char msg[BUF_SIZE];
					sprintf(msg,"Messagr received - %s",buf);
					nRecv = ::send(client,msg,strlen(msg),0);
					if(SOCKET_ERROR == nRecv)
					{
						printf("send failed! \n");
						break;
					}
				}
				
			}
		}
	//	printf("请输入要发送的消息：");
	//	scanf("%s",&szText);
	//	::send(client,szText,strlen(szText),0);
		// 关闭同客户端的连接
		::closesocket(client);
		
	}
	
	// 关闭监听套接字
	::closesocket(s);
	// 释放WS2_32库
	::WSACleanup();
	// 暂停，按任意键退出
	system("pause");
	return 0;
}
