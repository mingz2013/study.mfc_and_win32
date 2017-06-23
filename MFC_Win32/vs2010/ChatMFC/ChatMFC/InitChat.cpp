// InitChat.cpp
#include "stdafx.h"
#include "InitChat.h"
#include "ChatMFCDlg.h"
#include <WinSock.h>
#include <WS2tcpip.h>

//***************************************************************
HANDLE hThreadRecv; // �����߳�
SOCKET sock,sockM;
struct sockaddr_in local,remote;
short iPort = MCASTPORT;
char hostname[50] = {};
char LocalIP[20] = {};

/*
	����鲥ͨ�ţ��б���ʾ����

*/


void CChatMFCDlg::InitChat()
{// ��ʼ��
	//int ret;
	struct Msg MsgSend;
	//m_ListCtrl.InsertColumn(0,_T("���"),LVCFMT_LEFT,20);
	m_ListCtrl.InsertColumn(0,_T("������"),LVCFMT_LEFT,100);
	m_ListCtrl.InsertColumn(1,_T("IP��ַ"),LVCFMT_LEFT,100);
	m_ListCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	

	    // �õ�������----------------------------------------����
	
	int res = gethostname(hostname, sizeof(hostname));
	if (res != 0) {
		return ;
	}
	// ��ñ���ip
	hostent* host = gethostbyname(hostname);
	char* IP = inet_ntoa(*(struct in_addr*)*(host->h_addr_list)); 
	sprintf(LocalIP,"%s",IP); // �ϲ��ַ����� ip ��

	
	//bool bLoopBack = FALSE;
	
	//�����׽��֣�ʹ�öಥ���� 
	if((sock = WSASocket( AF_INET, SOCK_DGRAM, 0, NULL, 0,
		WSA_FLAG_MULTIPOINT_C_LEAF|
		WSA_FLAG_MULTIPOINT_D_LEAF|
		WSA_FLAG_OVERLAPPED)) == INVALID_SOCKET)
	{
		//AfxMessageBox();
		return ;
	}

	// �󶨱��ض˿ڣ�׼����������
	local.sin_family = AF_INET;
	local.sin_port = htons(iPort);
	local.sin_addr.S_un.S_addr = inet_addr(LocalIP);
	if(bind(sock,(struct sockaddr*)&local,sizeof(local)))
	{
		return;
	}

	// ���������ಥ���SOCKADDR_IN�ṹ��
	remote.sin_family = AF_INET;
	remote.sin_addr.S_un.S_addr = inet_addr(MCASTADDR);
	remote.sin_port = htons(iPort);

	/*/ �����ʵ���TTL
	int optval = 8;
	if(setsockopt(socket, IPPROTO_IP, IP_MULTICAST_TTL, (char*)&optval, sizeof(int)) == SOCKET_ERROR)
	{
		return;
	}


	*//* ������Ҫ���ûػ�
	if(bLoopBack)
	{*/
		int optval = 0;
		if(setsockopt(sock, IPPROTO_IP, IP_MULTICAST_TTL, (char*)&optval, sizeof(int)) == SOCKET_ERROR)
		{
			return;
		}

//	}

	// ����ಥ�飬sockMֻ�������뿪�ಥ�飬���������շ�����
	if((sockM = WSAJoinLeaf(sock,(SOCKADDR*)&remote, sizeof(remote), NULL, NULL, NULL, NULL, JL_BOTH)) == INVALID_SOCKET)
	{
		return;

	}

	/*/ ѡ���첽ͨ��ģʽ
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
	 
	// ����һ���߳�
	hThreadRecv = ::CreateThread(
		NULL,// Ĭ�ϰ�ȫ����
		NULL,// Ĭ�϶�ջ��С
		RecvMsg,// �߳���ڵ�ַ��ִ���̵߳ĺ�����
		this,// ���ݸ������Ĳ���
		0,// ָ���߳���������
		&dwThreadId);// �����̵߳�ID��
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
	CChatMFCDlg* pChatDlg = (CChatMFCDlg*)lparam;// ���ݵ���ָ��
	struct Msg MsgRecv;
	int iLen,Len;
	sockaddr_in from;
	struct DoMsgProcLP *lpDoMsgPorc;// �ṹ��ָ�룬����DoMsg�̵߳Ĳ���
	
	// ����
	pChatDlg->m_ListCtrl.InsertItem(0, _T("�������"));
	pChatDlg->m_ListCtrl.SetItemText(0, 1, _T("���ǲ���"));
	
	/*/ ��ʼ��ָ��
		lpDoMsgPorc->pChatDlg = (LPVOID)pChatDlg;
		lpDoMsgPorc->MsgRecv.Cmd = 1;
		lpDoMsgPorc->MsgRecv.HostName =(char) "qqq";
		lpDoMsgPorc->MsgRecv.IP = (char)"127.0.0.1";
	// ����һ���߳�
	DWORD dwThreadId;
	CreateThread(
		NULL,// Ĭ�ϰ�ȫ����
		NULL,// Ĭ�϶�ջ��С
		DoMsg,// �߳���ڵ�ַ��ִ���̵߳ĺ�����
		(LPVOID)lpDoMsgPorc,// ���ݸ������Ĳ�����---------------------��Ӧ�ô���һ���ṹ��ָ�룬�ṹ���������Ҫ���ݵĲ�����������ָ�룬���ͻ�������Ϣ��
		0,// ָ���߳���������
		&dwThreadId);// �����̵߳�ID��
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
		
		// ����
		CString strText;
		strText.Format(_T("%s"),inet_ntoa(from.sin_addr));
		AfxMessageBox(strText);

		// ��ʼ��ָ��
		lpDoMsgPorc->pChatDlg = (LPVOID)pChatDlg;
		lpDoMsgPorc->MsgRecv = MsgRecv;
	 
	// ����һ���߳�
	DWORD dwThreadId;
	CreateThread(
		NULL,// Ĭ�ϰ�ȫ����
		NULL,// Ĭ�϶�ջ��С
		DoMsg,// �߳���ڵ�ַ��ִ���̵߳ĺ�����
		(LPVOID)lpDoMsgPorc,// ���ݸ������Ĳ�����---------------------��Ӧ�ô���һ���ṹ��ָ�룬�ṹ���������Ҫ���ݵĲ�����������ָ�룬���ͻ�������Ϣ��
		0,// ָ���߳���������
		&dwThreadId);// �����̵߳�ID��
		
		
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
	
	// ����
	pChatDlg->m_ListCtrl.InsertItem(0, _T("�������"));
	pChatDlg->m_ListCtrl.SetItemText(0, 1, _T("���ǲ���"));
	
	switch(lpDoMsg->MsgRecv.Cmd)
		{
		case LOGOUT_CMD:
			{
				// ���ұ����б��ҵ���ɾ��
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
				// ���ұ����б�û�ҵ������,�����ͱ�����Ϣ
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
				// ���ұ����б�û�������
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
