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

	// ��ʼ��WS2_32.dll
	WSADATA wsaData;
	WORD sockVersion = MAKEWORD(2,0);
	::WSAStartup(sockVersion,&wsaData);
	// ����TCP Socket
	SOCKET s = ::socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(s == INVALID_SOCKET)
	{
		printf("Failed socket() \n");
		::WSACleanup();
		return 0;
	}
	 // �˿�
	int port;
	char addr[15];
	printf("    ������Զ������ip:");
	scanf("%s",&addr);
	printf("������Զ�������˿ں�:");
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
	printf("------================���ӳɹ�=============--\r\n");
	printf("---Sever: %s : %d========--\r\n",addr,port);

	char buf[BUF_SIZE]; // ��������
	while(true)
	{
		ZeroMemory(buf,BUF_SIZE);
		// ���������������
		printf("������Ҫ���͵���Ϣ��");
		//char str[BUF_SIZE];
		// �������������
		scanf("%s",&buf);
		
		// ���������������
		int nRecv = ::send(s,buf,strlen(buf),0);
		if(SOCKET_ERROR == nRecv)
		{
			printf("send failed! \n");
			closesocket(s);
			WSACleanup();
			return -1;
		}
		// ���շ������ش�������
		nRecv = ::recv(s,buf,sizeof(buf)+1,0);
		printf("Recv From Server: %s \n",buf);
		// ����յ���quit�����˳�
		if(strcmp(buf,"quit") == 0)
		{
			printf("quit! \n");
			break;
		}
	}

	

	// �ͷ���Դ
	::closesocket(s);
	::WSACleanup();
	// ��ͣ�������������
	system("pause");
	return 0;
}
