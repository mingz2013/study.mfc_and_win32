#pragma once
#include "stdafx.h"

#define SYSINFO		0x01
#define DISKINFO	0x02
#define FILELIST	0x03
#define DOWNLOAD	0x04

#define ID_FILE_MANAGER 1001  // 文件管理

#define ID_ONLINE	WM_USER + 1 // 上线消息
#define ID_OFFLINE	WM_USER + 2 /// 下线消息

typedef struct tagMSGINFO // 传输消息结构体
{
	int Msg_id;
	BYTE context[1024*5];
}MSGINFO;

typedef struct tagSYSTEMINFO // 上线消息
{
	int os;
	bool Cam; // 摄像头
	double ver;
}SYSTEMINFO;

typedef struct tagDRIVER
{
	wchar_t disk;
	double all;
	double free;
	int type;
}DRIVER;

typedef struct tagFILEINFO
{
    TCHAR FileName[256];
    int type;
    __int64 size;
}FILEINFO;

typedef struct tagDOWNFILEDATA
{
	bool flag;
	BYTE context[1024*5];
	UINT size;
	int count;

}DOWNFILEDATA;