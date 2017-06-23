// Server.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Server.h"
#include "winsock.h"
#include "SYS.h"

#pragma comment(lib,"ws2_32")

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

typedef struct
{
	int ID;
	BYTE lparam[2048];

}COMMAND;

DWORD WINAPI SLisen(LPVOID lpagram);
DWORD GetDriverProc(COMMAND command, SOCKET client);
/////////////////////////////////////////////////////////////////////////////
// The one and only application object

CWinApp theApp;

using namespace std;

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	WSAData wsadata;
	WORD ver = MAKEWORD(2,2);
	WSAStartup(ver, &wsadata);

	SOCKET server;
	server = socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN serveraddr;
	serveraddr.sin_family = AF_INET;
	int port = 12345;
	serveraddr.sin_port = htons(port);
	serveraddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);

	bind(server, (SOCKADDR*)&serveraddr, sizeof(serveraddr) );
	listen(server, 10);

	SOCKET client;
	char password[100];
	while(true)
	{
		if( (client = accept(server, 0, 0) ) != INVALID_SOCKET )
		{
			if( send( client, "Password", sizeof("Password"), 0 ) != SOCKET_ERROR )
			{
				printf("�пͻ��������ӣ����ڵȴ��ͻ���������......\n");
			}

			if( recv( client, password, sizeof(password), 0) == SOCKET_ERROR )
			{
				printf("�޷����ܿͻ�������\n");
				return 0;
			}
			else
			{
				if(strcmp(password,"12345") == 0)
				{
					send(client,"TRUE", sizeof("TRUE"), 0);
					printf("�û�����������ȷ\n");

					CreateThread(NULL, 0, SLisen, (LPVOID)client, 0, NULL);// �������Կͻ��˵�ָ��

					
				}
				else
				{
					send(client, "FALSE", sizeof("FALSE"), 0 );
					printf("�û������������\n");

				}
			}
		}
	}
	closesocket(server);
	closesocket(client);
	WSACleanup();

	return 0;
}

DWORD WINAPI SLisen(LPVOID lparam)
{
	SOCKET client = (SOCKET)lparam;
	COMMAND command;
	int i = 0;
	while(1)
	{
		
		i++;
		printf("while(1)ѭ���� %d ��\n",i);


		memset((char*)&command, 0, sizeof(command));
		if( recv(client, (char*)&command, sizeof(command), 0) == SOCKET_ERROR )
		{
			printf("����ָ�����\n");
			break;
		}
		else
		{
			switch(command.ID)
			{
			case GetDriver:
				GetDriverProc(command, client);//�õ�������Ϣ�����������ͻ���
				printf("�����о��꣬����\n");
				break;
			default:
				printf("��������\n");
				break;

			}
			printf("Ӧ��û�а�\n");
			
		}
		printf("whileѭ��β\n");

	}
	printf("whileѭ���˳�\n");
	closesocket(client);
	return 0;
}

DWORD GetDriverProc(COMMAND command, SOCKET client)
{
	COMMAND cmd;
	memset((char*)&cmd, 0, sizeof(cmd));
	cmd.ID = GetDriver; //��ͻ���˵��������Ϣ��ʲô
	
	for(char i = 'A'; i<='Z'; i++)
	{
		char x[20] = {i, ':', '\0'};
		UINT Type = GetDriveType(x);//ָ���̷�������

		if(Type == DRIVE_FIXED || Type == DRIVE_REMOVABLE || Type == DRIVE_CDROM)//   Ӳ��||�ƶ�Ӳ�̻�U��||���� 
		{
			memset((char*)cmd.lparam, 0, sizeof(cmd));
			strcpy((char*)cmd.lparam, x);

			if( send(client, (char*)&cmd, sizeof(cmd), 0 ) == SOCKET_ERROR)
			{
				printf("���ͻ��˷�����Ϣʧ��\n");
			}

		}
		printf("%c\n",i);
	}
	printf("forѭ������\n");
	return 0;

}
