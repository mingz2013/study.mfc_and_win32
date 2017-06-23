// Server.cpp : 定义控制台应用程序的入口点。
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

// 唯一的应用程序对象

CWinApp theApp;

using namespace std;

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	DWORD WINAPI SLisen(LPVOID lpParam);
	// TODO: 在此处为应用程序的行为编写代码。
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
		printf("监听失败\n");
		return 0;
	}
	SOCKET client = INVALID_SOCKET;
	sockaddr_in addr;
	int iLen = sizeof(sockaddr);
	printf("启动监听\n");
	while(TRUE)
	{
		client = accept(server, (sockaddr*)&addr, &iLen);
		if(INVALID_SOCKET == client)
		{
			printf("接收连接失败\n");
		}
		if( send( client, "Password", sizeof("Password"), 0 ) != SOCKET_ERROR )
		{
			printf("有客户请求连接，正在等待客户输入密码......\n");
		}
		if( recv( client, password, sizeof(password), 0) == SOCKET_ERROR )
		{
			printf("无法接受客户端密码\n");
			return 0;
		}
		if(strcmp(password,"12345") == 0)
		{
			send(client,"TRUE", sizeof("TRUE"), 0);
			printf("用户输入密码正确\n");

			CreateThread(NULL, 0, SLisen, (LPVOID)client, 0, NULL);// 接受来自客户端的指令
			//return 0;
		}
		else
		{
			send(client, "FALSE", sizeof("FALSE"), 0 );
			printf("用户输入密码错误\n");
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
		printf("while(1)循环第 %d 次\n",i);


		memset((char*)&command, 0, sizeof(command));
		if( recv(client, (char*)&command, sizeof(command), 0) == SOCKET_ERROR )
		{
			printf("接受指令错误\n");
			break;
		}
		else
		{
			switch(command.ID)
			{
			case GetDriver:
				{
					printf("GetDriver\n");
					GetDriverProc(command, client);//得到磁盘信息，并反馈给客户端
					/*COMMAND cmd;
					memset((char*)&cmd, 0, sizeof(cmd));
					cmd.ID = GetDriver;
					strcpy((char*)(cmd.lparam),"C:");
					//char cmd[1024] = "test";
					if( send(client, (char*)&cmd, sizeof(cmd), 0 ) == SOCKET_ERROR)
					{
						printf("给客户端反馈信息失败\n");
					}
					*/

					printf("磁盘列举完，返回\n");
				}
				break;
			default:
				printf("其他命令\n");
				break;

			}
			printf("应该没有吧\n");

		}
		printf("while循环尾\n");

	}
	printf("while循环退出\n");
	closesocket(client);
	return 0;
}

DWORD GetDriverProc(COMMAND command, SOCKET client)
{
	COMMAND cmd ;
	memset((char*)&cmd, 0, sizeof(cmd));
	cmd.ID = GetDriver; //向客户端说明返回信息是什么
	TCHAR x[3];
	UINT Type;
	for(wchar_t i = 'A'; i<='Z'; i++)
	{
		//printf("进入for循环%c\n",i);
		 //x[3] = {i, ':', '\0'};
		x[0] = i;
		x[1] = ':';
		x[2] = '\0';
		//UINT Type = GetDriveType((LPCWSTR)x);//指定盘符的类型
		 Type = GetDriveTypeW(x);//指定盘符的类型---------这里取不到盘符类型
		printf("%s盘符类型：%d\n",x,Type);
		if(Type == DRIVE_FIXED || Type == DRIVE_REMOVABLE || Type == DRIVE_CDROM)//   硬盘||移动硬盘或U盘||光盘 
		{
			memset((char*)(cmd.lparam), 0, sizeof(cmd));
			strcpy((char*)(cmd.lparam),(char*) x);
			printf("存在磁盘%c\n",i);
			printf("发送的信息cmd.lparam=%s\n", cmd.lparam);
			if( send(client, (char*)&cmd, sizeof(cmd), 0 ) == SOCKET_ERROR)
			{
				printf("给客户端反馈信息失败\n");
			}
			printf("发送磁盘信息成功\n");

		}
		//printf("%c\n",i);
	}
	printf("for循环结束\n");
	return 0;

}
