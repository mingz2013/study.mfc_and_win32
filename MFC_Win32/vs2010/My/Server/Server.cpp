// Server.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "Server.h"
#include "SYS.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
typedef struct
{
	int ID;
	BYTE lparam[2048];

}COMMAND;

DWORD WINAPI SLisen(LPVOID lpagram);
DWORD GetDriverProc(COMMAND command, SOCKET client);

// Ψһ��Ӧ�ó������

CWinApp theApp;

using namespace std;

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	DWORD WINAPI SLisen(LPVOID lpParam);
	// TODO: �ڴ˴�ΪӦ�ó������Ϊ��д���롣
	char password[20] = {0};
	WORD ver = MAKEWORD(2,2);
	WSAStartup(ver, &wsadata);
	server = socket(AF_INET, SOCK_STREAM, 0);
	sockaddr_in serveraddr;
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(port);
	serveraddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	bind(server, (sockaddr*)&serveraddr, sizeof(serveraddr));
	if(listen(server, 10) == SOCKET_ERROR)
	{
		printf("����ʧ��\n");
		return 0;
	}
	SOCKET client = INVALID_SOCKET;
	sockaddr_in addr;
	int iLen = sizeof(sockaddr);
	printf("��������\n");
	while(TRUE)
	{
		client = accept(server, (sockaddr*)&addr, &iLen);
		if(INVALID_SOCKET == client)
		{
			printf("��������ʧ��\n");
		}
		if( send( client, "Password", sizeof("Password"), 0 ) != SOCKET_ERROR )
		{
			printf("�пͻ��������ӣ����ڵȴ��ͻ���������......\n");
		}
		if( recv( client, password, sizeof(password), 0) == SOCKET_ERROR )
		{
			printf("�޷����ܿͻ�������\n");
			return 0;
		}
		if(strcmp(password,"12345") == 0)
		{
			send(client,"TRUE", sizeof("TRUE"), 0);
			printf("�û�����������ȷ\n");

			CreateThread(NULL, 0, SLisen, (LPVOID)client, 0, NULL);// �������Կͻ��˵�ָ��
			//return 0;
		}
		else
		{
			send(client, "FALSE", sizeof("FALSE"), 0 );
			printf("�û������������\n");
		}
	}
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
				{
					printf("GetDriver\n");
					GetDriverProc(command, client);//�õ�������Ϣ�����������ͻ���
					/*COMMAND cmd;
					memset((char*)&cmd, 0, sizeof(cmd));
					cmd.ID = GetDriver;
					strcpy((char*)(cmd.lparam),"C:");
					//char cmd[1024] = "test";
					if( send(client, (char*)&cmd, sizeof(cmd), 0 ) == SOCKET_ERROR)
					{
						printf("���ͻ��˷�����Ϣʧ��\n");
					}
					*/

					printf("�����о��꣬����\n");
				}
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
	COMMAND cmd ;
	memset((char*)&cmd, 0, sizeof(cmd));
	cmd.ID = GetDriver; //��ͻ���˵��������Ϣ��ʲô
	TCHAR x[3];
	UINT Type;
	for(wchar_t i = 'A'; i<='Z'; i++)
	{
		//printf("����forѭ��%c\n",i);
		 //x[3] = {i, ':', '\0'};
		x[0] = i;
		x[1] = ':';
		x[2] = '\0';
		//UINT Type = GetDriveType((LPCWSTR)x);//ָ���̷�������
		 Type = GetDriveTypeW(x);//ָ���̷�������---------����ȡ�����̷�����
		printf("%s�̷����ͣ�%d\n",x,Type);
		if(Type == DRIVE_FIXED || Type == DRIVE_REMOVABLE || Type == DRIVE_CDROM)//   Ӳ��||�ƶ�Ӳ�̻�U��||���� 
		{
			memset((char*)(cmd.lparam), 0, sizeof(cmd));
			strcpy((char*)(cmd.lparam),(char*) x);
			printf("���ڴ���%c\n",i);
			printf("���͵���Ϣcmd.lparam=%s\n", cmd.lparam);
			if( send(client, (char*)&cmd, sizeof(cmd), 0 ) == SOCKET_ERROR)
			{
				printf("���ͻ��˷�����Ϣʧ��\n");
			}
			printf("���ʹ�����Ϣ�ɹ�\n");

		}
		//printf("%c\n",i);
	}
	printf("forѭ������\n");
	return 0;

}
