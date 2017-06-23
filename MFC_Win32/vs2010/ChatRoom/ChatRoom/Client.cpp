#include "stdafx.h"
#include "ChatRoomDlg.h"
#include "Inc.h"


DWORD WINAPI CChatRoomDlg::ConnectThreadFunc(LPVOID pParam)
{
	CChatRoomDlg*pChatRoom = (CChatRoomDlg*)pParam;
	ASSERT(pChatRoom != NULL);
	

	pChatRoom->m_ConnectSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(pChatRoom->m_ConnectSock == INVALID_SOCKET)
	{
		AfxMessageBox(_T("新建socket失败！"));
		return FALSE;
	}
	CString strServIp;
	pChatRoom->GetDlgItemText(IDC_IPADDRESS, strServIp);
	int uPort =pChatRoom->GetDlgItemInt(IDC_EDIT_SERVERPORT);
	if(uPort<0||uPort>65535)
	{
		AfxMessageBox(_T("请输入正确的端口1~65535"));
		goto _Error_End;
	}
	char szIpAddr[16] = {0};
	USES_CONVERSION;
	strcpy_s(szIpAddr, 16, T2A(strServIp));
	sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_addr.S_un.S_addr = inet_addr(szIpAddr);
	server.sin_port = htons(uPort);

	if( connect(pChatRoom->m_ConnectSock, (sockaddr*)&server, sizeof(sockaddr_in)) == SOCKET_ERROR)
	{
		AfxMessageBox(_T("连接服务器失败！"));
		goto _Error_End;
	}
	pChatRoom->ShowMsg(_T("系统信息： 连接服务器成功！"));
	pChatRoom->m_bIsServer = FALSE;
	while(TRUE && !(pChatRoom->bShutDown))
	{
		if(pChatRoom->SOCKET_Select(pChatRoom->m_ConnectSock, 100, TRUE))
		{
			TCHAR szBuf[MAX_BUF_SIZE] = {0};
			int iRet = recv(pChatRoom->m_ConnectSock, (char*)szBuf, MAX_BUF_SIZE, 0);// 返回接收到的字节数
			if(iRet)
			{
				//strMsg.Format(_T("%s"),szBuf);
				//strMsg = szBuf;
				//strMsg = _T("客户端：") + m_ClientItem.m_strIp + _T(">");
				pChatRoom->ShowMsg(szBuf);
			}
			else
			{// 客户端离开不用自己写代码，socket内部完成
				//strMsg = _T("客户端：") + m_ClientItem.m_strIp + _T(">离开聊天室！");
				pChatRoom->ShowMsg(_T("系统消息： 聊天服务器已停止，请重新连接！"));
				//m_ClientItem.m_pMainWnd->RemoveClientFromArray(m_ClientItem);
				break;

			}
			
		}
		Sleep(500);
	}
_Error_End:
	closesocket(pChatRoom->m_ConnectSock);
	return TRUE;
}

void CChatRoomDlg::StopClient()
{
	bShutDown = TRUE;
	DWORD dwRet = WaitForSingleObject(m_hConnectThread, 1000);
	if(dwRet != WAIT_OBJECT_0)
	{
		TerminateThread(m_hConnectThread, -1);
		closesocket(m_ConnectSock);
	}
	m_hConnectThread = NULL;
	m_ConnectSock = INVALID_SOCKET;
	m_bIsServer = -1;
	bShutDown = FALSE;
}