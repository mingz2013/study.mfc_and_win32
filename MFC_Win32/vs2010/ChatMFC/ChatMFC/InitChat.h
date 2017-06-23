
#pragma once
//#include "stdafx.h"


#pragma comment(lib,"Ws2_32.lib") 

#define MCASTADDR "234.5.6.7"
#define MCASTPORT 25000

#define LOGIN_CMD 0x01
#define LOGOUT_CMD 0x02
#define LOG_CMD 0x03

#define MSGSIZE 100

struct Msg{// 传递的消息结构体
	int Cmd;
	char HostName[50];
	char IP[20];
};

struct DoMsgProcLP{// 调用DoMsg线程的参数指针的结构体
	LPVOID pChatDlg;
	Msg MsgRecv;

}; 

//void DoMsg(struct Msg MsgRecv);
//DWORD WINAPI DoMsgPrc(LPVOID lparam);

