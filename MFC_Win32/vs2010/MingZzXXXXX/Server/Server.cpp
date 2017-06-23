// Server.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


#include "ThreadMain.h"

#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib,"User32.lib")
#pragma comment(lib,"Advapi32.lib")



void Server();
void Server()
{
    CThreadMain Thread_Main;
	Thread_Main.RunFlag = TRUE;
    Thread_Main.GetInfo(); //获取配置信息
	/*
    if(Auto[1] == '1')
    {
        wcscpy_s(Thread_Main.MyServiceName,(wchar_t*)ServiceName);
    }
	*/
    while(true)
    {
        if(Thread_Main.RunFlag == false)
        {
            break;
        }
        SOCKET sock;
        sock = Thread_Main.Run();
        Thread_Main.Command(sock);
    }
}

int _tmain(int argc, _TCHAR* argv[])
{
	Server();
	return 0;
}

