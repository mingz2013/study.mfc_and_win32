// PortScan.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include<winsock.h>

#pragma comment(lib, "ws2_32")
// ���ر����ͷ�ļ��Ϳ��ļ�
void usage(char *prog)
{
	printf("Usage:GSGBannerScan.exe 127.0.0.1 1 65535\n");
	printf("GSGBannerScan.exe IP Strtport Endport\n");
}
// �Զ����������
int main(int argc, char* argv[])
{
	if(argc != 4)
	{
		usage( argv[0] );
		return -1;
	}// �����������4������ʾ����
	WSADATA wsa;
	if ( WSAStartup( MAKEWORD(2,2), &wsa ) != 0 )
	{
		printf("Winsock Dll init Failed! \n");
		return -1;
	}// ��ʼ��Socket�汾
	int nowport, count;
	// ���嵱ǰ�˿ںͼ�����
	struct sockaddr_in sa;
	int startport = atoi(argv[2]);
	int endport = atoi(argv[3]);
	// ���ÿ�ʼ�˿ںͽ����˿�
	if( endport < startport )
	{
		printf("don&#39;t doing,endport < startport\n");
		return -1;
	}
	// �ж϶˿ڵ���Ч��
	nowport = startport;
	// ���õ�ǰ�˿� = ��ʼ�˿�
	printf("Start scan.......\n");
	for( nowport; nowport < endport; nowport++)
	{
		printf("Scanning port--------- %d----------\n",nowport);
		sa.sin_family = AF_INET;
		sa.sin_addr.S_un.S_addr = inet_addr(argv[1]);
		sa.sin_port = htons(nowport);
		// ����Ŀ������
		SOCKET sockFD = socket( AF_INET, SOCK_STREAM, 0);
		if( sockFD == INVALID_SOCKET )
		{
			printf("Socket create Error!\n");
			return -1;
		}// ����socket�׽���
		int iTimeOut = 5000;// ���ó�ʱ
		setsockopt( sockFD, SOL_SOCKET, SO_RCVTIMEO, (char*)&iTimeOut,sizeof(iTimeOut));
		if( connect( sockFD, (const sockaddr*)&sa, sizeof(sa) ) == SOCKET_ERROR )
		{
			closesocket(sockFD);
		}// ������Ӵ���
		else
		{
			count = count + 1; // ���ӳɹ�����������1
			printf("%s Find %d Port is Opend!\n",argv[1],nowport);
			if( nowport == 21 )
			{
				char buff[2048] = {0};
				char hello[5] = {"test"};
				send( sockFD, hello, sizeof(hello), 0 );
				recv( sockFD, buff, sizeof(buff), 0 );
				printf("FTP Banner: %s\n",buff);
				// ������Լ���send(sockFD,"ftp",3,0)
				// ....���ж�ftp�Ƿ����������¼��дȨ�ޣ��ȵ�
				/*
				{
				send(client,"ftp",3,0);
				......ͨ�������û��������룬Ȼ����շ����ж��Ƿ���Ե�¼
				}
				*/
				// ��Щ��������ɶ��������
			}// �����21�˿ڣ���ʾ�˿�banner
			else
			{
				if( nowport == 80 )
				{
					char buff[2048] = {0};
					char get[30] = {"GET HTTP 1.0/1.1\n\n\r\r\r"};
					send( sockFD, get, sizeof(get), 0 );
					recv( sockFD, buff, sizeof(buff), 0);
					printf("The server is %s\n",buff);
				}// �����80�˿ڣ���ʾbannner
				//else if (nowport == %d xx)
				// ������Լ�������banner�ж�
				// ��Щ��������ɶ��������
				closesocket(sockFD);
			}
		}

	}
	printf("Scan End......\nFind %d Port is Opend!\n",count); // ��������԰ѽ��д��һ���ı��ĵ���
	// ��ʾ����
	WSACleanup();
	// �ͷ�socket��Դ
	return 0;
}
