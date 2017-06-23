// InitChat.cpp
#include "stdafx.h"
#include "InitChat.h"
#include "ChatMFCDlg.h"
#include <WinSock.h>
#include <WS2tcpip.h>

//***************************************************************
HANDLE hThreadRecv; // 接收线程
SOCKET sock,sockM;
struct sockaddr_in local,remote;
short iPort = MCASTPORT;
char hostname[50] = {};
char LocalIP[20] = {};

/*
	完成组播通信，列表显示部分

*/


void CChatMFCDlg::InitChat()
{// 初始化
	//int ret;
	struct Msg MsgSend;
	//m_ListCtrl.InsertColumn(0,_T("编号"),LVCFMT_LEFT,20);
	m_ListCtrl.InsertColumn(0,_T("主机名"),LVCFMT_LEFT,100);
	m_ListCtrl.InsertColumn(1,_T("IP地址"),LVCFMT_LEFT,100);
	m_ListCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	

	    // 得到主机名----------------------------------------测试
	
	int res = gethostname(hostname, sizeof(hostname));
	if (res != 0) {
		return ;
	}
	// 获得本地ip
	hostent* host = gethostbyname(hostname);
	char* IP = inet_ntoa(*(struct in_addr*)*(host->h_addr_list)); 
	sprintf(LocalIP,"%s",IP); // 合并字符串到 ip 中

	
	//bool bLoopBack = FALSE;
	
	//创建套接字，使用多播属性 
	if((sock = WSASocket( AF_INET, SOCK_DGRAM, 0, NULL, 0,
		WSA_FLAG_MULTIPOINT_C_LEAF|
		WSA_FLAG_MULTIPOINT_D_LEAF|
		WSA_FLAG_OVERLAPPED)) == INVALID_SOCKET)
	{
		//AfxMessageBox();
		return ;
	}

	// 绑定本地端口，准备接收数据
	local.sin_family = AF_INET;
	local.sin_port = htons(iPort);
	local.sin_addr.S_un.S_addr = inet_addr(LocalIP);
	if(bind(sock,(struct sockaddr*)&local,sizeof(local)))
	{
		return;
	}

	// 建立描述多播组的SOCKADDR_IN结构体
	remote.sin_family = AF_INET;
	remote.sin_addr.S_un.S_addr = inet_addr(MCASTADDR);
	remote.sin_port = htons(iPort);

	/*/ 设置适当的TTL
	int optval = 8;
	if(setsockopt(socket, IPPROTO_IP, IP_MULTICAST_TTL, (char*)&optval, sizeof(int)) == SOCKET_ERROR)
	{
		return;
	}


	*//* 根据需要禁用回环
	if(bLoopBack)
	{*/
		int optval = 0;
		if(setsockopt(sock, IPPROTO_IP, IP_MULTICAST_TTL, (char*)&optval, sizeof(int)) == SOCKET_ERROR)
		{
			return;
		}

//	}

	// 加入多播组，sockM只是用于离开多播组，不能用来收发数据
	if((sockM = WSAJoinLeaf(sock,(SOCKADDR*)&remote, sizeof(remote), NULL, NULL, NULL, NULL, JL_BOTH)) == INVALID_SOCKET)
	{
		return;

	}

	/*/ 选择异步通信模式
	ret = WSAAsyncSelect(sock, hWnd, WM_USER + 1001,FD_WRITE|FD_READ|FD_QOS|FD_GROUP_QOS|FD_CONNECT);
	if(ret == SOCKET_ERROR)
	{
		return;
	}

	*/

	
	/*
	m_ListCtrl.InsertItem(0,_T("0"));
	m_ListCtrl.SetItemText(0,1,_T("01"));
	
/*
	CString strText = m_ListCtrl.GetItemText(0,0);
	AfxMessageBox(strText);

	int nCount = m_ListCtrl.GetSelectedCount();
	//CString strText;
	strText.Format(_T("%d"),nCount);
	AfxMessageBox(strText);
	*/

	DWORD dwThreadId;
	 
	// 创建一个线程
	hThreadRecv = ::CreateThread(
		NULL,// 默认安全属性
		NULL,// 默认堆栈大小
		RecvMsg,// 线程入口地址（执行线程的函数）
		this,// 传递给函数的参数
		0,// 指定线程立即运行
		&dwThreadId);// 返回线程的ID号
	//::CloseHandle(hThreadRecv);
	
	
	//memset((void*)&MsgSend, 0, sizeof(MsgSend));
	MsgSend.Cmd = LOGIN_CMD;
	//MsgSend.HostName = hostname;
	//MsgSend.IP = LocalIP;
	strcpy(MsgSend.HostName,hostname);
	strcpy(MsgSend.IP,LocalIP);
	SendMsg((char*)&MsgSend);
}



void CChatMFCDlg::SendMsg(char* MsgSend)
{
	if(sendto(sock, MsgSend, strlen(MsgSend), 0, (struct sockaddr*)&remote, sizeof(remote)) == SOCKET_ERROR)
	{
		return ;
	}

}

DWORD WINAPI CChatMFCDlg::RecvMsg(LPVOID lparam)
{
	CChatMFCDlg* pChatDlg = (CChatMFCDlg*)lparam;// 传递的类指针
	struct Msg MsgRecv;
	int iLen,Len;
	sockaddr_in from;
	struct DoMsgProcLP *lpDoMsgPorc;// 结构体指针，传给DoMsg线程的参数
	
	// 测试
	pChatDlg->m_ListCtrl.InsertItem(0, _T("测试语句"));
	pChatDlg->m_ListCtrl.SetItemText(0, 1, _T("还是测试"));
	
	/*/ 初始化指针
		lpDoMsgPorc->pChatDlg = (LPVOID)pChatDlg;
		lpDoMsgPorc->MsgRecv.Cmd = 1;
		lpDoMsgPorc->MsgRecv.HostName =(char) "qqq";
		lpDoMsgPorc->MsgRecv.IP = (char)"127.0.0.1";
	// 创建一个线程
	DWORD dwThreadId;
	CreateThread(
		NULL,// 默认安全属性
		NULL,// 默认堆栈大小
		DoMsg,// 线程入口地址（执行线程的函数）
		(LPVOID)lpDoMsgPorc,// 传递给函数的参数，---------------------这应该传递一个结构体指针，结构体包含所有要传递的参数，比如类指针，发送回来的消息等
		0,// 指定线程立即运行
		&dwThreadId);// 返回线程的ID号
		*/
	

	while(1)
	{
		memset((char*)&MsgRecv, 0, sizeof(MsgRecv));
		memset((char*)&from, 0, sizeof(from));
		//memset((char*)&MsgSend, 0, sizeof(MsgSend));
		
		if((iLen = recvfrom(sock, (char*)&MsgRecv, MSGSIZE, 0, (struct sockaddr*)&from, &Len)) == SOCKET_ERROR)
		{
			return FALSE;
		}
		
		// 测试
		CString strText;
		strText.Format(_T("%s"),inet_ntoa(from.sin_addr));
		AfxMessageBox(strText);

		// 初始化指针
		lpDoMsgPorc->pChatDlg = (LPVOID)pChatDlg;
		lpDoMsgPorc->MsgRecv = MsgRecv;
	 
	// 创建一个线程
	DWORD dwThreadId;
	CreateThread(
		NULL,// 默认安全属性
		NULL,// 默认堆栈大小
		DoMsg,// 线程入口地址（执行线程的函数）
		(LPVOID)lpDoMsgPorc,// 传递给函数的参数，---------------------这应该传递一个结构体指针，结构体包含所有要传递的参数，比如类指针，发送回来的消息等
		0,// 指定线程立即运行
		&dwThreadId);// 返回线程的ID号
		
		
		//Sleep(100);
		
		// DoMsg(MsgRecv);
	}
	return TRUE;

}

DWORD WINAPI CChatMFCDlg::DoMsg(LPVOID lparam)
{
	DoMsgProcLP * lpDoMsg = (DoMsgProcLP *)lparam;
	struct Msg MsgSend;
	CChatMFCDlg* pChatDlg = (CChatMFCDlg*)lpDoMsg->pChatDlg;
	//pChatDlg->m_ListCtrl;
	//pChatDlg->SendMsg
	
	// 测试
	pChatDlg->m_ListCtrl.InsertItem(0, _T("测试语句"));
	pChatDlg->m_ListCtrl.SetItemText(0, 1, _T("还是测试"));
	
	switch(lpDoMsg->MsgRecv.Cmd)
		{
		case LOGOUT_CMD:
			{
				// 查找本地列表，找到后删除
				CString strText;
				for(int i = 0; i< pChatDlg->m_ListCtrl.GetSelectedCount(); i++)
				{
					CString strText = pChatDlg->m_ListCtrl.GetItemText(i,1);
					if(strcmp(lpDoMsg->MsgRecv.IP,(char*)strText.GetBuffer()) == 0)
					{
						//m_ListCtrl.DeleteItem(i);
						for(int j = i; j < pChatDlg->m_ListCtrl.GetSelectedCount(); i++)
						{
							pChatDlg->m_ListCtrl.SetItemText(j, 0, pChatDlg->m_ListCtrl.GetItemText(j+1, 0));
							pChatDlg->m_ListCtrl.SetItemText(j, 1, pChatDlg->m_ListCtrl.GetItemText(j+1, 1));


						}
						pChatDlg->m_ListCtrl.DeleteItem(pChatDlg->m_ListCtrl.GetSelectedCount() - 1);
						
						break;
					}
				}
				/*
				AfxMessageBox(strText);

				int nCount = m_ListCtrl.GetSelectedCount();
				//CString strText;
				strText.Format(_T("%d"),nCount);
				AfxMessageBox(strText); 
				*/
			}

			break;
		case LOGIN_CMD:
			{
				// 查找本地列表，没找到则添加,并发送本机信息
				CString strText;
				for(int i = 0; i< pChatDlg->m_ListCtrl.GetSelectedCount(); i++)
				{
					CString strText = pChatDlg->m_ListCtrl.GetItemText(i,1);
					if(strcmp(lpDoMsg->MsgRecv.IP,(char*)strText.GetBuffer()) != 0)
					{
						continue;
					}
					pChatDlg->m_ListCtrl.InsertItem(pChatDlg->m_ListCtrl.GetSelectedCount(),(LPCTSTR)lpDoMsg->MsgRecv.HostName);
					pChatDlg->m_ListCtrl.SetItemText(pChatDlg->m_ListCtrl.GetSelectedCount(),1,(LPCTSTR)lpDoMsg->MsgRecv.IP);

					MsgSend.Cmd = LOG_CMD;
					//MsgSend.HostName = hostname;
					//MsgSend.IP = LocalIP;
					strcpy(MsgSend.HostName,hostname);
					strcpy(MsgSend.IP,LocalIP);
					pChatDlg->SendMsg((char*)&MsgSend);
				}

			}
			break;
		case LOG_CMD:
			{
				// 查找本地列表，没有则添加
				CString strText;
				for(int i = 0; i< pChatDlg->m_ListCtrl.GetSelectedCount(); i++)
				{
					CString strText = pChatDlg->m_ListCtrl.GetItemText(i,1);
					if(strcmp(lpDoMsg->MsgRecv.IP,(char*)strText.GetBuffer()) != 0)
					{
						continue;
					}
					pChatDlg->m_ListCtrl.InsertItem(pChatDlg->m_ListCtrl.GetSelectedCount(),(LPCTSTR)lpDoMsg->MsgRecv.HostName);
					pChatDlg->m_ListCtrl.SetItemText(pChatDlg->m_ListCtrl.GetSelectedCount(),1,(LPCTSTR)lpDoMsg->MsgRecv.IP);

					MsgSend.Cmd = LOG_CMD;
					//MsgSend.HostName = hostname;
					//MsgSend.IP = LocalIP;
					strcpy(MsgSend.HostName,hostname);
					strcpy(MsgSend.IP,LocalIP);
					pChatDlg->SendMsg((char*)&MsgSend);
				}
			}
			break;
		default:
			break;


		}
	return TRUE;

}
