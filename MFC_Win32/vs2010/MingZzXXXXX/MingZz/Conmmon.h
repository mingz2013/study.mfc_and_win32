#pragma once
#include "stdafx.h"

#define SYSINFO		0x01
#define DISKINFO	0x02
#define FILELIST	0x03
#define DOWNLOAD	0x04

#define ID_FILE_MANAGER 1001  // �ļ�����

#define ID_ONLINE	WM_USER + 1 // ������Ϣ
#define ID_OFFLINE	WM_USER + 2 /// ������Ϣ

typedef struct tagMSGINFO // ������Ϣ�ṹ��
{
	int Msg_id;
	BYTE context[1024*5];
}MSGINFO;

typedef struct tagSYSTEMINFO // ������Ϣ
{
	int os;
	bool Cam; // ����ͷ
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