// client.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<winsock2.h>
#include<stdio.h>
#include<windows.h>
#pragma comment(lib,"WS2_32.lib")

void decode(treenode htree[],int c[],int n,int num){ 
	
	int ch,m=0; 
	
	
	
	ch=c[m]; 
	
	while(m<n){   
		
		int i; 
		
		for(i=2*num-2;htree[i].l!=-1;){ 
			
			if(ch==0)     i=htree[i].l; 
			
			else 
				
				i=htree[i].r; 
			
			m++; 
			
			ch=c[m]; 
			
		} 
		
		printf("%c",htree[i].c); 
		
	}  
	
} 

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
	printf("------================���ӳɹ�=============--\r\n\n");
	char buff[256]; // ��������
	int nRecv = ::recv(s,buff,256,0);
	decode(htree,c,n,29);
	if(nRecv > 0)
	{
		buff[nRecv] = '\0';
		printf("�յ���Ϣ��%s \n",buff);
	}
	::closesocket(s);
	::WSACleanup();
	return 0;
}
