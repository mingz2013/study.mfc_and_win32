#include "StdAfx.h"
#include "Disk.h"
#include "Common.h"
#include "afxcmn.h"
//#include <Windows.h>



CDisk::CDisk(void)
{
}


CDisk::~CDisk(void)
{
}

void CDisk::SendDrivers(SOCKET sock)
{
	BOOL fResult;
	DRIVER dir;
	MSGINFO_S msg;
	memset(&msg, 0, sizeof(MSGINFO_S));
	msg.Msg_id = DISKINFO;
	for(wchar_t d = 'A'; d <= 'Z'; d++)
	{
		memset(&dir, 0, sizeof(DRIVER));
		memset(msg.context, 0, sizeof(msg.context));
		unsigned _int64 i64FreeBytesToCaller;
		unsigned _int64 i64TotalBytes;
		unsigned _int64 i64FreeBytes;
		TCHAR szTemp[3] = {d, ':', '\0'};
		UINT uType = GetDriveTypeW(szTemp);
		switch(uType)
		{
		case DRIVE_FIXED:
			{
				dir.type = 1;
				break;
			}
		case DRIVE_CDROM:
			{
				dir.type = 2;
				break;
			}
		case DRIVE_REMOTE:
			{
				dir.type = 3;
				break;
			}
		default:
			{
				continue;
			}
		}
		fResult = GetDiskFreeSpaceEx(szTemp, (PULARGE_INTEGER)&i64FreeBytesToCaller, (PULARGE_INTEGER)&i64TotalBytes, (PULARGE_INTEGER)&i64FreeBytes);
		dir.disk = d;
		if(fResult)
		{
			dir.all = (double)(i64TotalBytes/1024.0/1024/1024);
			dir.free = (double)(i64FreeBytesToCaller/1024.0/1024/1024);
		}
		else
		{
			dir.all = 0.0;
			dir.free = 0.0;
		}

		memcpy(msg.context, &dir, sizeof(DRIVER));
		Sleep(0);
		m_sock.MySend(sock, (char*)&msg, sizeof(MSGINFO_S));
	}
}


void CDisk::SendFileList(wchar_t fp[260],SOCKET sock)
{
    WIN32_FIND_DATAW FindData;
    memset(&FindData,0,sizeof(WIN32_FIND_DATAW));
    HANDLE hError;
    int FileCount = 0;
    TCHAR FilePathName[1024];
 // 构造路径
    wchar_t Path[1024];
    wcscpy_s(Path,fp);
    wsprintfW(FilePathName,_T("%s\\*.*"),Path);
    hError = FindFirstFileW(FilePathName, &FindData);
    FILEINFO fileinfo;
    DWORDLONG dl;
    dl = MAXDWORD;
    MSGINFO_S msg;
    memset(&msg,0,sizeof(MSGINFO_S));
    msg.Msg_id = FILELIST;
    if(hError == INVALID_HANDLE_VALUE)
    {
        printf("搜索失败!\n");
        //发送结束信息
        //return;
    }
    while(::FindNextFile(hError, &FindData))
    {
  // 过虑.和..
        if(wcscmp(FindData.cFileName,_T(".")) == 0 || wcscmp(FindData.cFileName,_T("..")) == 0 )
        {
            continue;
        }
  // 构造完整路径
        //wsprintfW(FullPathName,_T("%s\\%s"), Path,FindData.cFileName);
        //FileCount++;
  // 输出本级的文件
        wsprintfW(fileinfo.FileName,_T("%s"),FindData.cFileName);
        //wprintf(_T("%s\n"),FindData.cFileName);
        if((FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
        {
            fileinfo.type = 1; //<Dir>
        }
        else
        {
            fileinfo.type = 0; //<File>
            fileinfo.size = ((__int64)FindData.nFileSizeHigh * (dl+1)) + (__int64)FindData.nFileSizeLow;
        }
        
        memcpy(msg.context,(char*)&fileinfo,sizeof(FILEINFO));
        m_sock.MySend(sock,(char*)&msg,sizeof(MSGINFO_S));
        memset(&FindData,0,sizeof(WIN32_FIND_DATAW));
    }
    fileinfo.type = 2;
    memcpy(msg.context,(char*)&fileinfo,sizeof(FILEINFO));
    m_sock.MySend(sock,(char*)&msg,sizeof(MSGINFO_S));
    return;
}

void CDisk::DownFile(SOCKET sock,wchar_t DownPath[260])
{
    MSGINFO_S msg;
    memset(&msg,0,sizeof(MSGINFO_S));
    msg.Msg_id = DOWNLOAD;
    DOWNFILEDATA fis;
    memset(&fis,0,sizeof(DOWNFILEDATA));

    CFile file(DownPath,CFile::modeRead);
    ULONGLONG u = file.GetLength();
    fis.flag = true;
    if(u <= 512) //文件不足一个块
    {
        file.Read(fis.context,(UINT)u);
        fis.size = (UINT)u;
        fis.count = 0;
        memcpy(msg.context,&fis,sizeof(DOWNFILEDATA));
        m_sock.MySend(sock,(char*)&msg,sizeof(MSGINFO_S));
    }
    else
    {
        ULONGLONG Count;
        Count = u / 512 + 1;
        int Last = u % 512;
        for(int i=0;i<Count;i++)
        {
            memset(fis.context,0,512);
            if(i == Count - 1) //这是最后一次传送文件数据
            {
                file.Read(fis.context,Last);
                fis.size = Last;
            }
            else
            {
                file.Read(fis.context,512);
                fis.size = 512;
            }
            fis.count = i;
            memcpy(msg.context,&fis,sizeof(DOWNFILEDATA));
            m_sock.MySend(sock,(char*)&msg,sizeof(MSGINFO_S));
        }
    }
    fis.flag = false;
    memcpy(msg.context,&fis,sizeof(DOWNFILEDATA));
    m_sock.MySend(sock,(char*)&msg,sizeof(MSGINFO_S));
    file.Close();
    ::CloseHandle(file.m_hFile);
}