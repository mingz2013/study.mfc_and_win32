
#pragma once
//#include "stdafx.h"


#pragma comment(lib,"Ws2_32.lib") 

#define MCASTADDR "234.5.6.7"
#define MCASTPORT 25000

#define LOGIN_CMD 0x01
#define LOGOUT_CMD 0x02
#define LOG_CMD 0x03

#define MSGSIZE 100

struct Msg{// ���ݵ���Ϣ�ṹ��
	int Cmd;
	char HostName[50];
	char IP[20];
};

struct DoMsgProcLP{// ����DoMsg�̵߳Ĳ���ָ��Ľṹ��
	LPVOID pChatDlg;
	Msg MsgRecv;

}; 

//void DoMsg(struct Msg MsgRecv);
//DWORD WINAPI DoMsgPrc(LPVOID lparam);

