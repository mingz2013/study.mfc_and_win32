#include "stdafx.h"
#include "ChatRoomDlg.h"
#include"Inc.h"


DWORD WINAPI CChatRoomDlg::ListenThreadFunc(LPVOID pParam)
{
	CChatRoomDlg*pChatRoom = (CChatRoomDlg*)pParam;
	ASSERT(pChatRoom != NULL);
	

	pChatRoom->m_ListenSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(pChatRoom->m_ListenSock == INVALID_SOCKET)
	{
		AfxMessageBox(_T("新建socket失败！"));
		return FALSE;
	}
	int uPort =pChatRoom->GetDlgItemInt(IDC_EDIT_LOCALPORT);
	if(uPort<0||uPort>65535)
	{
		AfxMessageBox(_T("请输入正确的端口1~65535"));
		goto _Error_End;
	}
	sockaddr_in service;
	service.sin_family = AF_INET;
	service.sin_addr.S_un.S_addr = INADDR_ANY;
	service.sin_port = htons(uPort);

	if( bind(pChatRoom->m_ListenSock, (sockaddr*)&service, sizeof(sockaddr_in)) == SOCKET_ERROR)
	{
		AfxMessageBox(_T("绑定端口失败！"));
		goto _Error_End;
	}
	if(listen(pChatRoom->m_ListenSock, 5) == SOCKET_ERROR)
	{
		AfxMessageBox(_T("监听端口失败"));
		goto _Error_End;
	} 
	pChatRoom->m_bIsServer = TRUE;
	pChatRoom->ShowMsg(_T("系统消息： 服务器已开启，等待客户连接！"));
	while(TRUE && !(pChatRoom->bShutDown))
	{
		if(pChatRoom->SOCKET_Select(pChatRoom->m_ListenSock, 100, TRUE))
		{
			sockaddr_in clientAddr;
			int iLen = sizeof(sockaddr_in);
			SOCKET accSock = accept(pChatRoom->m_ListenSock, (struct sockaddr*)&clientAddr, &iLen);

			if(accSock == INVALID_SOCKET)
			{
				//AfxMessageBox(_T("接受客户端失败"));
				//goto _Error_End;
				continue;
			}
			
			CClientItem tItem;
			tItem.m_Socket = accSock;
			tItem.m_pMainWnd = pChatRoom;
			tItem.m_strIp = inet_ntoa(clientAddr.sin_addr);
			INT_PTR idx = pChatRoom->m_ClientArray.Add(tItem);
			tItem.hThread = CreateThread(NULL,
				0,
				ClientThreadProc, 
				&(pChatRoom->m_ClientArray.GetAt(idx)),
				CREATE_SUSPENDED,// 线程挂起
				NULL);
			pChatRoom->m_ClientArray.GetAt(idx).hThread = tItem.hThread;// 最后一个成员赋值，完整了
			ResumeThread(tItem.hThread);// 恢复被挂起的线程

			pChatRoom->ShowMsg(_T("系统消息：") + tItem.m_strIp + _T("进入聊天室"));
			
			Sleep(100);
		}
	}

_Error_End:
	closesocket(pChatRoom->m_ListenSock);
	return TRUE;

}


BOOL CChatRoomDlg::SOCKET_Select(SOCKET hSocket, int nTimeOut, BOOL bRead)
{
	fd_set fdset;
	timeval tv;
	FD_ZERO(&fdset);
	FD_SET(hSocket, &fdset);
	nTimeOut = nTimeOut>1000?1000:nTimeOut;
	tv.tv_sec = 0;
	tv.tv_usec = nTimeOut;

	int iRet = 0;
	if(bRead)
	{
		iRet = select(0, &fdset, NULL, NULL, &tv);
	}
	else
	{
		iRet = select(0, NULL, &fdset, NULL, &tv);
	}

	if(iRet<=0)
	{
		return FALSE;
	}
	else if(FD_ISSET(hSocket, &fdset))
	{
		return TRUE;
	}
	return FALSE;
}


void CChatRoomDlg::ShowMsg(CString strMsg)
{
	m_EditChatShow.SetSel(-1, -1);// 把光标定位到文本最后位置
	m_EditChatShow.ReplaceSel(strMsg + _T("\r\n"));// 将光标替换为文本信息
}

void CChatRoomDlg::RemoveClientFromArray(CClientItem in_Item)
{
	for(int idx = 0; idx < m_ClientArray.GetCount(); idx++)
	{
		CClientItem tItem = m_ClientArray.GetAt(idx);
		if(tItem.m_Socket == in_Item.m_Socket &&
			tItem.hThread == in_Item.hThread &&
			tItem.m_strIp == in_Item.m_strIp)
		{
			m_ClientArray.RemoveAt(idx);
		}
	}
}

DWORD WINAPI CChatRoomDlg::ClientThreadProc(LPVOID lpParameter)
{
	CString strMsg;
	CClientItem m_ClientItem = *(CClientItem*)lpParameter;
	while(TRUE && !(m_ClientItem.m_pMainWnd->bShutDown))
	{
		if(m_ClientItem.m_pMainWnd->SOCKET_Select(m_ClientItem.m_Socket, 100, TRUE))
		{
			TCHAR szBuf[MAX_BUF_SIZE] = {0};
			int iRet = recv(m_ClientItem.m_Socket, (char*)szBuf, MAX_BUF_SIZE, 0);// 返回接收到的字节数
			if(iRet)
			{
				//strMsg.Format(_T("%s"),szBuf);
				strMsg = szBuf;
				strMsg = _T("客户端：") + m_ClientItem.m_strIp + _T(">") + strMsg;
				m_ClientItem.m_pMainWnd->ShowMsg(strMsg);
				m_ClientItem.m_pMainWnd->SendClientsMsg(strMsg, &m_ClientItem);
			}
			else
			{// 客户端离开不用自己写代码，socket内部完成
				strMsg = _T("客户端：") + m_ClientItem.m_strIp + _T(">离开聊天室！");
				m_ClientItem.m_pMainWnd->ShowMsg(strMsg);
				m_ClientItem.m_pMainWnd->RemoveClientFromArray(m_ClientItem);
				break;

			}
			
		}
		Sleep(500);
	}
	return TRUE;
}

void CChatRoomDlg::SendClientsMsg(CString strMsg, CClientItem* pNotSend)
{
	TCHAR szBuf[MAX_BUF_SIZE] = {0};
	_tcscpy_s(szBuf, MAX_BUF_SIZE, strMsg);
	for(INT_PTR idx = 0; idx < m_ClientArray.GetCount(); idx++)
	{
		if(!pNotSend||
			pNotSend->m_Socket != m_ClientArray.GetAt(idx).m_Socket||
			pNotSend->hThread != m_ClientArray.GetAt(idx).hThread||
			pNotSend->m_strIp != m_ClientArray.GetAt(idx).m_strIp)
		{
			send(m_ClientArray.GetAt(idx).m_Socket, (char*)szBuf, _tcslen(szBuf)*sizeof(TCHAR), 0);
		}
	}
}

void CChatRoomDlg::StopServer()
{
	UINT nCount = m_ClientArray.GetCount();
	HANDLE *m_pHandles = new HANDLE[nCount + 1];
	m_pHandles[0] = m_hListenThread;
	for(int idx = 0; idx < nCount; idx++)
	{
		m_pHandles[idx + 1] = m_ClientArray.GetAt(idx).hThread;
	}
	bShutDown = TRUE;
	DWORD dwRet = WaitForMultipleObjects(nCount + 1, m_pHandles, TRUE , 1000);
	if(dwRet != WAIT_OBJECT_0)
	{
		for(INT_PTR i = 0; i < m_ClientArray.GetCount(); i++)
		{
			TerminateThread(m_ClientArray.GetAt(i).hThread, -1);
			closesocket(m_ClientArray.GetAt(i).m_Socket);
		}
		TerminateThread(m_hListenThread, -1);
		closesocket(m_ListenSock);
	}
	delete [] m_pHandles;
	m_hListenThread = NULL;
	m_ListenSock = INVALID_SOCKET;
	m_bIsServer = -1;
	bShutDown = FALSE;

}