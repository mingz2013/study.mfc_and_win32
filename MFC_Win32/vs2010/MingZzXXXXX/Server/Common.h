#pragma once
#include <windows.h>
#define SYSINFO		0x01
#define DISKINFO	0x02
#define FILELIST	0x03
#define DOWNLOAD	0x04

typedef struct tagMSGINFO //传输消息结构体
{
    int Msg_id;
    BYTE context[1024*5];
}MSGINFO_S;

typedef struct tagSYSTEMINFO
{
    int os;
    bool Cam; //摄像头
    double ver;
}SYSTEMINFO_S;

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

typedef struct tagTEMPSTRUCT
{
	BYTE context[1024*5];
	SOCKET sock;
	DWORD t;
}TEMPSTRUCT;