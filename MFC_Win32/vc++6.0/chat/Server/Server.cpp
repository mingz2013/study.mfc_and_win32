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
	// ���sockaddr_in �ṹ
	sockaddr_in sin;
	sin.sin_family = AF_INET;
        // �˿�
	int port;
	printf("������󶨵ı��ض˿ں�:");
	scanf("%d",&port);
	sin.sin_port = htons(port);
	sin.sin_addr.S_un.S_addr = INADDR_ANY;
	// ������׽��ֵ�һ�����ص�ַ
	if(::bind(s,(LPSOCKADDR)&sin,sizeof(sin)) == SOCKET_ERROR)
	{
		printf("Failed bind() \n");
		::WSACleanup();
		return 0;
	}
	// �л�������״̬
	if(::listen(s,2) == SOCKET_ERROR)
	{
		printf("Failed listen()");
		::WSACleanup();
		return 0;
	}
	printf("������� %d �˿ڼ����С�����\n\n",port);
	
	SOCKET client; // ִ��accept()���½�����������ͨ�ŵ��׽���
	sockaddr_in remoteAddr; // ���ڽ��ս����ַ
        int len = sizeof(remoteAddr);
	char szText[] = " Server\r\n";
	

	while(TRUE)
	{
		// �ȴ����ս�������
		client = ::accept(s,(SOCKADDR*)&remoteAddr,&len);
		if(client == INVALID_SOCKET)
		{
			printf("Failed accept()"); // ��ӡ�������
			return 0;
		}
		else
		{
			printf("********************* �ӵ����ӣ� %s : %d **************\r\n",inet_ntoa(remoteAddr.sin_addr),remoteAddr.sin_port); // ��ӡ�����ַ
		}
		while(true)
		{
			//printf("------================���ӳɹ�=============--\r\n\n");
			
			char buf[BUF_SIZE]; // ��������
			ZeroMemory(buf,BUF_SIZE); // ��ս������ݵĻ�����
			int nRecv = ::recv(client,buf,BUF_SIZE,0);
			if(SOCKET_ERROR == nRecv)
			{
				printf("recv failed! \n");
				break;
			}
			//��ȡ��ǰϵͳʱ��
			SYSTEMTIME st;
			GetLocalTime(&st);
			char sDateTime[30];
			if(nRecv > 0)
			{
				buf[nRecv] = '\0';
				printf("%4d-%2d-%2d %2d:%2d:%2d",st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond);
				// ��ӡ�����Ϣ
				printf("Recv From Client [%s:%d] :%s\n",inet_ntoa(remoteAddr.sin_addr),remoteAddr.sin_port,buf);
				// ����ͻ��˷��͡�quit���ַ�������������˳�
				if(strcmp(buf,"quit") == 0)
				{
					nRecv = ::send(client,"quit",strlen("quit"),0);
					break;
				}
				// ������ͻ��˷��ͻ����ַ���
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
	//	printf("������Ҫ���͵���Ϣ��");
	//	scanf("%s",&szText);
	//	::send(client,szText,strlen(szText),0);
		// �ر�ͬ�ͻ��˵�����
		::closesocket(client);
		
	}
	
	// �رռ����׽���
	::closesocket(s);
	// �ͷ�WS2_32��
	::WSACleanup();
	// ��ͣ����������˳�
	system("pause");
	return 0;
}
